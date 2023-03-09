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
#include "ftp_server_connection_listener.h"

using namespace std;

/** @brief closes a socket
 *
 *  This function closes the socket defined by sockDescriptor
 *
 *  @param sockDescriptor file descriptor of the socket
 */

void closeSocket(int& sockDescriptor)
{
    close(sockDescriptor);
}

/** @brief Retrieves port number from socketDescriptor
 *
 *  This function retrieves port number from socketDescriptor
 *
 *  @param sockDescriptor file descriptor of the socket
 *
 *  @return an integer value denoting prot number 
 */

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

/** @brief Checks if Socket is ready to read data
 *
 *  This function waits for a given amount of time to check if any data is received from the remote computer.
 *
 *  @param sockDescriptor file descriptor of the socket
 *  @param timeoutSec amount of time to wait in seconds
 *  @param timeoutUSec amount of time to wait in micro seconds
 *  @param isError boolean value denoting the occurance of an error
 *  @param istimedout boolean value denoting the end of waiting period
 *
 *  @return a boolean value denoting if the socket is ready to read data or not 
 */

bool isSocketReadyToRead(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool& isTimedout)
{
    fd_set readfds;
    struct timeval tv;
    int valueReturned;

    tv.tv_sec = timeoutSec;
    tv.tv_usec = timeoutUSec;

    FD_ZERO(&readfds);
    FD_SET(sockDescriptor, &readfds);
    
    valueReturned = select(MAX_CLIENT_CONNECTIONS + 1, &readfds, NULL, NULL, &tv);

    if(valueReturned == -1)
    {
       isError = true;
       return false;
    }

    else if(valueReturned == 0)
    {
       isTimedout = true;
       return false;
    }

    else

       return true;

}

/** @brief Retrieves Host IP
 *
 *  This function retrieves host name and IP
 *
 *  @return a character array containing the IP address 
 */

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
