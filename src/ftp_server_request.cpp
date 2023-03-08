/**
 * @file ftp_server_request.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 08, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_request.h" file
 *
 */

#include "ftp_server_request.h"

void interpretFtpRequest(const char* ftpRequest, ClientFtpSession& clientFtpSession)
{

}

void parseFtpRequest(const char* ftpRequest, char* requestName, char* requestArgument)
{

}


void handleFtpRequestUSER(const char* username, ClientFtpSession& clientFtpSession)
{

}

void handleFtpRequestPASS(const char* password, ClientFtpSession& clientFtpSession)
{

}

void handleFtpRequestPWD(ClientFtpSession& clientFtpSession)
{

}

void handleFtpRequestCWD(const char* directory, ClientFtpSession& clientFtpSession)
{

}

void handleFtpRequestCDUP(ClientFtpSession& clientFtpSession)
{

}

void handleFtpRequestPASV(ClientFtpSession& clientFtpSession)
{

}

void handleFtpRequestNLST(ClientFtpSession& clientFtpSession)
{

}

void handleFtpRequestRETR(const char* file, ClientFtpSession& clientFtpSession)
{

}

void handleFtpRequestQUIT(ClientFtpSession& clientFtpSession)
{

}

void handleFtpRequestUnSupported(ClientFtpSession& clientFtpSession)
{

}

void handleNotLoggedIn(ClientFtpSession& clientFtpSession)
{

}

