/**
 * @file ftp_server_nlist.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 08, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_nlist.h" file
 *
 */

#include <iostream>
#include <dirent.h>
#include <string>
#include <string.h>
#include "ftp_server_connection_listener.h"
#include "ftp_server_nlist.h"
#include "ftp_server_connection.h"

using namespace std;

int listDirEntries(int dataSockDescriptor)
{
    DIR* directory;
    struct dirent* directoryEntry;
    string fileName, entryInfo; 
    string fileType = "U";
    int numEntries = 0;
    unsigned short fileSize;

    if((directory = opendir(DEFAULT_DIRECTORY_PATH)) == NULL)
    {
        perror("opendir() failed");
    }
    else
    {
        errno = 0;

        while((directoryEntry = readdir(directory)))
        {
            fileName = directoryEntry->d_name;

            if(directoryEntry->d_type == DT_DIR)  // Determining the file type 
            {
                fileType = "D";
            }

            else if(directoryEntry->d_type == DT_REG) 
            {
                fileType = "F";
            }

            if(fileType == "F") // This entry is a regular file so determining its size
            {
                fileSize = directoryEntry->d_reclen;
                entryInfo = fileType + "       " + fileName + "            " + to_string(fileSize) + "\n";
            }

            else

                entryInfo = fileType + "       " + fileName + "\n";

            numEntries++;

            int status = sendToRemote(dataSockDescriptor, entryInfo.c_str(), strlen(entryInfo.c_str()));
    
            if(status < 0)

                cout << "Encountered an error while sending data\n";
        }

        if(errno != 0)
        {
            perror("readdir() failed");
        }
    }

    return numEntries;
}
