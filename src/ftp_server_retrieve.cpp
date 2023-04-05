/**
 * @file ftp_server_retrieve.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date April 05, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_retrieve.h" file
 *
 */

#define _POSIX_SOURCE
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstdio>
#include "ftp_server_connection_listener.h"
#include "ftp_server_nlist.h"
#include "ftp_server_connection.h"
#include "ftp_server_retrieve.h"
#include "ftp_server_response.h"

using namespace std;

/** @brief Sends a File to FTP client application
 *
 *  This function sends a file to the client application if the file is accessible. 
 *
 *  @param filename a character array that holds the filename
 *  @param dataSockDescriptor an integer denoting data connection socket
 */
int sendFile(const char* filename, int& dataSockDescriptor)
{
    int accessStatus = -1;
    int bytesRead = 0;
    int fileSize = 0;
    int sendToByteCount = 0;
    char buffer[DATA_SOCKET_SEND_BUFFER_SIZE];
    
    accessStatus = access(filename, R_OK);
    
    if(accessStatus == 0)
    {
        FILE* file = fopen(filename, FILE_OPEN_MODE);
        
        if(!file)
        {
            perror("cannot open file");
        }

        else
        {
            fseek(file, 0, SEEK_END);
            fileSize = ftell(file);
            sendToByteCount = fileSize;
            fseek(file, 0, SEEK_SET);

            while(sendToByteCount > 0)
            {
                if(sendToByteCount >= DATA_SOCKET_SEND_BUFFER_SIZE)
                {
                    bytesRead = fread(buffer, 1, DATA_SOCKET_SEND_BUFFER_SIZE, file);

                    if(bytesRead <= 0)
                    {
                        perror("fread() failed");
                    }

                    else
                    {
                        int status = sendToRemote(dataSockDescriptor, buffer, DATA_SOCKET_SEND_BUFFER_SIZE);

                        if(status < 0)

                            cout << "Encountered an error while sending data\n";

                        sendToByteCount -= bytesRead;
                    }
                }

                else
                {
                    bytesRead = fread(buffer, 1, sendToByteCount, file);

                    if(bytesRead <= 0)
                    {
                        perror("fread() failed");
                    }

                    else
                    {
                        int status = sendToRemote(dataSockDescriptor, buffer, sendToByteCount);

                        if(status < 0)

                            cout << "Encountered an error while sending data\n";

                        sendToByteCount -= bytesRead;
                    }
                }
            }
        }
    }

    

    return fileSize;
}
