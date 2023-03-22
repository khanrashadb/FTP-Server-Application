/**
 * @file ftp_server_session.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 08, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_session.h" file
 *
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include "ftp_server_session.h"
#include "ftp_server_connection.h"
#include "ftp_server_response.h"

using namespace std;

void startClientFTPSession(ClientFtpSession& clientFtpSession)
{   
    char path[256];
    size_t pathLength = sizeof(path);
    bool isReady = false;
    bool isError = false;
    bool isTimedout = false;
    int status = sendToRemote(clientFtpSession.controlConnection, CONNECTED_RESPONSE, sizeof(CONNECTED_RESPONSE));
    
    if(status < 0)

        cout << "Encountred an error while sending data\n";

    clientFtpSession.isControlConnected = true;

    int bytesReturned = readlink("/proc/self/exe", path, pathLength);
    
    if(bytesReturned > 0)
    {
        path[bytesReturned] = '\0';
        strcpy(clientFtpSession.rootDir, path);
    }

    while(clientFtpSession.isControlConnected)
    {
        isReady = isConnectionReadyToRead(clientFtpSession.controlConnection, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isError, isTimedout);

        if(isReady == false)

            cout << "Error! Connection is not reading\n";
    }   
}

void stopClientFTPSession(ClientFtpSession& clientFtpSession)
{

}
