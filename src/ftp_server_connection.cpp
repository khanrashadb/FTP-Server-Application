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

/** @brief Send data to the remote computer
 *
 *  This function sends message of mesageLength to the remote computer
 *
 *  @param sockDescriptor file descriptor of the socket
 *  @param message an array containing the message to be sent
 *  @param messageLength the length of the message
 *
 *  @return an integer value denoting the status of the process
 */
int sendToRemote(const int sockDescriptor, const char* message, const int messageLength)
{
    return send(sockDescriptor, message, messageLength, 0);
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
bool isConnectionReadyToRead(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool&isTimedout)
{
    return isSocketReadyToRead(sockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
}

/** @brief Receives data from the remote computer
 *
 *  This function receives messages of upto mesageLength from the remote computer
 *
 *  @param sockDescriptor file descriptor of the socket
 *  @param message an array containing the message to be sent
 *  @param messageLength the length of the message
 *
 *  @return an integer value denoting the status of the process
 */
int receiveFromRemote(const int sockDescriptor, char* message, int messageLength)
{
    ssize_t bytesReturned = recv(sockDescriptor, message, messageLength, 0);
    
    if(bytesReturned >= 0)

        message[bytesReturned] = '\0';

    return bytesReturned;
}

/** @brief closes a socket
 *
 *  This function closes the socket defined by sockDescriptor
 *
 *  @param sockDescriptor file descriptor of the socket
 */

void closeConnection(int& sockDescriptor)
{
    close(sockDescriptor);
}
