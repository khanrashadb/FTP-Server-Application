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
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "ftp_server_connection_listener.h"
#include "ftp_server_nlist.h"

using namespace std;

int listDirEntries(int dataSockDescriptor)
{
    return 1;
}
