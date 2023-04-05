/**
 * @file ftp_server_retrieve.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 08, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_retrieve.h" file
 *
 */

#include <iostream>
#include <dirent.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "ftp_server_connection_listener.h"
#include "ftp_server_nlist.h"
#include "ftp_server_connection.h"
#include "ftp_server_retrieve.h"

int sendFile(const char* filename, int& dataSockDescriptor)
{
    DIR* directory;
    struct dirent* directoryEntry;
    bool accessible = false;

    if((directory = opendir(DEFAULT_DIRECTORY_PATH)) == NULL)
    {
        perror("opendir() failed");
    }
    else
    {
        errno = 0;

        while((directoryEntry = readdir(directory)))
        {
            if(directoryEntry->d_type == DT_REG)
            {
                if(strcmp(filename, directoryEntry->d_name) == 0)

                    accessible = true;
            }
        }

        if(errno != 0)
        {
            perror("readdir() failed");
        }

        else if(accessible == true)
        {
            FILE* file = fopen(filename, FILE_OPEN_MODE);
        }

    }
    return 1;
}
