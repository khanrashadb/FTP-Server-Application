/**
 * @file ftp_server_connection.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 08, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_connection.h" file
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
#include "ftp_server_connection.h"
#include "ftp_server_net_util.h"

using namespace std;

int sendToRemote(const int sockDescriptor, const char* message, const int messageLength)
{
    return send(sockDescriptor, message, messageLength, 0);
}

bool isConnectionReadyToRead(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool&isTimedout)
{
    return isSocketReadyToRead(sockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
}

int receiveFromRemote(const int sockDescriptor, char* message, int messageLength)
{
    ssize_t bytesReturned = recv(sockDescriptor, message, messageLength, 0);
    
    if(bytesReturned >= 0)

        message[bytesReturned] = '\0';

    return bytesReturned;
}

void closeConnection(int& sockDescriptor)
{
    close(sockDescriptor);
}
