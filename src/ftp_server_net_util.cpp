/**
 * @file ftp_server_net_util.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 08, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_net_util.h" file
 *
 */

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <ctime>
#include "ftp_server_net_util.h"
#include "ftp_server_connection.h"

using namespace std;

void closeSocket(int& sockDescriptor)
{
    close(sockDescriptor);
}

int getPortFromSocketDescriptor(const int sockDescriptor)
{
    int port;
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if(getsockname(sockDescriptor, (struct sockaddr*)&sin, &len) == -1)
    {
        perror("getsockname");
        return -1;
    }

    else
    {
        port = ntohs(sin.sin_port);
        return port;
    }
}

bool isSocketReadyToRead(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool& isTimedout)
{
    double delay = timeoutSec + (0.000001 * timeoutUSec);
    int messageLength = 1024;
    char message[messageLength];
    int bytesReturned = 0;

    delay = delay * CLOCKS_PER_SEC;
    clock_t now = clock();

    isError = false;
    isTimedout = false;

    while((clock() - now) <= delay)
    {
        bytesReturned = receiveFromRemote(sockDescriptor, message, messageLength);

        if(bytesReturned == -1)
        {
            isError = true;
            break;
        }

        if(bytesReturned > 0)

            break;
    }

    if(bytesReturned == 0)

        isTimedout = true;

    if(bytesReturned > 0)

        return true;
    
    else 

        return false;
}

char* getHostIPAddress()
{
    char host[256];
    int hostName;
    struct hostent *host_entry;

    hostName = gethostname(host, sizeof(host));

    if (hostName == -1)
    {
        perror("gethostname");
        exit(1);
    }

    host_entry = gethostbyname(host);

    if (host_entry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }

    return inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
}
