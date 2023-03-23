/**
 * @file ftp_server_session.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 22, 20213
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
#include "ftp_server_request.h"

using namespace std;

/** @brief Starts a client FTP session
 *
 *  This sends a connected response to the client
 *  then while the client stays connected, it interprets 
 *  requests from the client and stops the session if client requestss are 
 *  timed out.
 *
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */

void startClientFTPSession(ClientFtpSession& clientFtpSession)
{   
    char path[256];
    char requestBuffer[FTP_REQUEST_BUFFER_SIZE];
    bool isReady = false;
    bool isError = false;
    bool isTimedout = false;
    int receivedBytes;
    int status = sendToRemote(clientFtpSession.controlConnection, CONNECTED_RESPONSE, strlen(CONNECTED_RESPONSE));
    
    if(status < 0)

        cout << "Encountered an error while sending data\n";

    clientFtpSession.isControlConnected = true;

    if(getcwd(path, sizeof(path)) != NULL)

        clientFtpSession.rootDir = strdup(path);

    while(clientFtpSession.isControlConnected)
    {
        isReady = isConnectionReadyToRead(clientFtpSession.controlConnection, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isError, isTimedout);

        if(isReady == true)
        {
            receivedBytes = receiveFromRemote(clientFtpSession.controlConnection, requestBuffer, FTP_REQUEST_BUFFER_SIZE);
        
            if(receivedBytes < 0)
            {
                status = sendToRemote(clientFtpSession.controlConnection, INTERNAL_ERROR_RESPONSE, strlen(INTERNAL_ERROR_RESPONSE));
            }

            else
            
                interpretFtpRequest(requestBuffer, clientFtpSession);
            
        }

        else
        {
            if(isTimedout == true)
            {
                status = sendToRemote(clientFtpSession.controlConnection, PASSIVE_ERROR_TIMEOUT_RESPONSE, strlen(PASSIVE_ERROR_TIMEOUT_RESPONSE));
    
                stopClientFTPSession(clientFtpSession);
            }

	    else if(isError == true)
	    {
		status = sendToRemote(clientFtpSession.controlConnection, INTERNAL_ERROR_RESPONSE, strlen(INTERNAL_ERROR_RESPONSE));

		stopClientFTPSession(clientFtpSession);
	    }
        }
    }   
}

/** @brief Stops a client FTP session
 *
 *  This function resets all clientFtpSession Data to close a 
 *  client FTP session.
 *
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */
 
void stopClientFTPSession(ClientFtpSession& clientFtpSession)
{
    closeConnection(clientFtpSession.controlConnection);
    closeConnection(clientFtpSession.dataConnection);
    closeConnection(clientFtpSession.dataListener);
    clientFtpSession.controlConnection = -1;
    clientFtpSession.dataConnection = -1;
    clientFtpSession.dataListener = -1;
    clientFtpSession.isControlConnected = false;
    clientFtpSession.isDataConnected = false;
    clientFtpSession.isDataListener = false;
    clientFtpSession.isValidUser = false;
    clientFtpSession.isLoggedIn = false;
    clientFtpSession.rootDir = NULL;
}
