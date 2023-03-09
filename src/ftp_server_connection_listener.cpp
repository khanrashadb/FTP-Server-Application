/**
 * @file ftp_server_connection_listener.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 08, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_connection_listener.h" file
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
#include "ftp_server_net_util.h"

using namespace std;

/** @brief Starts a listener socket
 *
 *  This function creates a socket binds it and starts listening for client connections
 *
 *  @param port the port to listen to
 *  @param listenerSockDescriptor file descriptor of the listener socket
 *  @param succeded a boolean value denoting the succes of the procedure
 */

void startListenerSocket(char* port, int& listenerSockDescriptor, bool& succeded)
{
    bool errorFound = false;
    int yes = 1;
    char serverIP[MAX_IP_ADDRESS_LENGTH];
    strcpy(serverIP, getHostIPAddress());

    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    if(getaddrinfo(serverIP, port, &hints, &res) != 0)
    
        errorFound = true;

    if((listenerSockDescriptor = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    {
        perror("server: socket");
        errorFound = true;
    }
    
    if(setsockopt(listenerSockDescriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        errorFound = true;
    }

    if(bind(listenerSockDescriptor, res->ai_addr, res->ai_addrlen) == -1)
    {
        closeSocket(listenerSockDescriptor);
        perror("server: bind");
        errorFound = true;
    }

    if(listen(listenerSockDescriptor, 10) == -1)
    {
        perror("listen");
        errorFound = true;
    }

    if(errorFound == false)
    
        succeded = true;
}

/** @brief Checks if Listener Socket is ready to read data
 *
 *  This function waits for a given amount of time to check if any data is received from the remote computer.
 *
 *  @param listenerSockDescriptor file descriptor of the socket
 *  @param timeoutSec amount of time to wait in seconds
 *  @param timeoutUSec amount of time to wait in micro seconds
 *  @param isError boolean value denoting the occurance of an error
 *  @param istimedout boolean value denoting the end of waiting period

 *  @return a boolean value denoting if the socket is ready to read data or not 
 */
bool isListenerSocketReady(const int listenerSockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool&isTimedout)
{
    return isSocketReadyToRead(listenerSockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
}

/** @brief Accepts a client connection
 *
 *  This function accepts client connections
 *
 *  @param listenerSockDescriptor file descriptor of the socket to be closed
 *  @param clientSockDescriptor socket descriptor of the client
 */
void acceptClientConnection(const int listenerSockDescriptor, int& clientSockDescriptor)
{
    struct sockaddr_storage client_addr;
    socklen_t sin_size = sizeof(client_addr);
    clientSockDescriptor = accept(listenerSockDescriptor, (struct sockaddr*)&client_addr, &sin_size);
}

/** @brief closes a socket
 *
 *  This function closes the socket defined by listenerSockDescriptor
 *
 *  @param listenerSockDescriptor file descriptor of the socket to be closed
 */

void closeListenerSocket(int& listenerSockDescriptor)
{
    close(listenerSockDescriptor);
}

