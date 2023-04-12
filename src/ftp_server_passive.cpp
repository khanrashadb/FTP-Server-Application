/**
 * @file ftp_server_passive.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 08, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_passive.h" file
 *
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <algorithm>
#include "ftp_server_connection_listener.h"
#include "ftp_server_passive.h"
#include "ftp_server_response.h"
#include "ftp_server_connection.h"
#include "ftp_server_net_util.h"
#include "ftp_server_request.h"

using namespace std;

/** @brief Enters passive mode
 *
 *  This function enters passive mode by opening a datalistener socket. Once a client is  
 *  ready to connect it accepts a data connection from the client.
 *
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */
void enteringIntoPassive(ClientFtpSession& clientFtpSession)
{
    bool succeded;
    
    startPassiveListener(clientFtpSession, succeded);

    if(succeded)
    {
        bool isError = false;
        bool isTimedout = false;
        bool isReady = false;
        char response[256];

        createPassiveSuccessResponse(response, clientFtpSession.dataListener);

        int status = sendToRemote(clientFtpSession.controlConnection, response, strlen(response));
    
        if(status < 0)

            cout << "Encountered an error while sending data\n";

        isReady = isListenerSocketReady(clientFtpSession.dataListener, DATA_CONNECTION_TIME_OUT_SEC, DATA_CONNECTION_TIME_OUT_USEC, isError, isTimedout);
    
        if(isReady == true)
        {
            acceptClientConnection(clientFtpSession.dataListener, clientFtpSession.dataConnection);
            stopPassiveListener(clientFtpSession);
        
            int status = sendToRemote(clientFtpSession.controlConnection, DATA_CONNECTION_SUCCESS_RESPONSE, strlen(DATA_CONNECTION_SUCCESS_RESPONSE));
    
            if(status < 0)

                cout << "Encountered an error while sending data\n";
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
		        status = sendToRemote(clientFtpSession.controlConnection, PASSIVE_ERROR_RESPONSE, strlen(INTERNAL_ERROR_RESPONSE));

		        stopClientFTPSession(clientFtpSession);
	        }
        }
    
    }
}

/** @brief Starts connection listener for passive mode
 *
 *  This function starts a connection listener for starting passive mode by opening a datalistener socket. Updates the status 
 *  upon success and failure.
 *
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 *  @param succeded a bollean variable denoting the status of the procedure
 */
void startPassiveListener(ClientFtpSession& clientFtpSession, bool& succeded)
{
    char dataListenerPort[] = "5021";
    startListenerSocket(dataListenerPort, clientFtpSession.dataListener, succeded);
}

/** @brief leaves passive mode
 *
 *  This function leaves passive mode by closing the datalistener socket.
 *
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */
void stopPassiveListener(ClientFtpSession& clientFtpSession)
{
    closeListenerSocket(clientFtpSession.dataListener);
}

/** @brief Creates passive success response
 *
 *  This function creates appropriate passive success response to send to the client 
 *
 *  @param response a character array that holds the response 
 *  @param passiveListenerSockDescriptor an integer denoting passive listener socket
 */
void createPassiveSuccessResponse(char* response, const int passiveListenerSockDescriptor)
{
    int portFirstDecimal = getPortFromSocketDescriptor(passiveListenerSockDescriptor) / 256;
    int portSecondDecimal = getPortFromSocketDescriptor(passiveListenerSockDescriptor) % 256;

    string IP(getHostIPAddress());
    replace(IP.begin(), IP.end(), '.', ',');

    sprintf(response, PASSIVE_SUCCESS_RESPONSE, IP.c_str(), portFirstDecimal, portSecondDecimal);
}
