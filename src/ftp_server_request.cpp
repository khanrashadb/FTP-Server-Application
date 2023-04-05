/**
 * @file ftp_server_request.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 22, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_request.h" file
 *
 */
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include "ftp_server_session.h"
#include "ftp_server_connection.h"
#include "ftp_server_response.h"
#include "ftp_server_request.h"
#include "ftp_server_passive.h"
#include "ftp_server_nlist.h"

using namespace std;

/** @brief Interpretes client request
 *
 *  This function interperetes client requests by matching the request
 *  against valid requests and processes the request if its valid and sends a 
 *  success response. It sends an invalid request response otherwise
 *  timed ou.
 *
 *  @param ftpRequest a character array that holds the request received from client
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */

void interpretFtpRequest(const char* ftpRequest, ClientFtpSession& clientFtpSession)
{
    char* requestName = new char[FTP_REQUEST_CODE_CHARACTER_COUNT];
    char* requestArgument = new char[FTP_REQUEST_ARG_MAX_CHARACTER_COUNT];

    cout << "FTP Server: Received command " << ftpRequest << "\n";
    
    parseFtpRequest(ftpRequest, requestName, requestArgument);

    if(strcmp(requestName, FTP_REQUEST_USER) == 0)

        handleFtpRequestUSER(requestArgument, clientFtpSession);

    else if(strcmp(requestName, FTP_REQUEST_PASSWORD) == 0)

        handleFtpRequestPASS(requestArgument, clientFtpSession);
        
    else if(strcmp(requestName, FTP_REQUEST_PWD) == 0)
    
        handleFtpRequestPWD(clientFtpSession);
    
    else if(strcmp(requestName, FTP_REQUEST_CWD) == 0)

        handleFtpRequestCWD(requestArgument, clientFtpSession);

    else if(strcmp(requestName, FTP_REQUEST_CDUP) == 0)

        handleFtpRequestCDUP(clientFtpSession);

    else if(strcmp(requestName, FTP_REQUEST_QUIT) == 0)

        handleFtpRequestQUIT(clientFtpSession);

    else if(strcmp(requestName, FTP_REQUEST_PASV) == 0)

        handleFtpRequestPASV(clientFtpSession);

    else if(strcmp(requestName, FTP_REQUEST_NLST) == 0)

        handleFtpRequestNLST(clientFtpSession);

    else

        handleFtpRequestUnSupported(clientFtpSession);    

    free(requestName);
    free(requestArgument);
}

/** @brief Parses client FTP requests
 *
 *  This function splits client request into request name and request 
 *  argument using the request delimiter.
 *
 *  @param ftpRequest a character array that holds the request received from client
 *  @param requestName a character array that holds the name of the request
 *  @param requestArgument a character array that holds the argument of the request
 */

void parseFtpRequest(const char* ftpRequest, char* requestName, char* requestArgument)
{
    string req(ftpRequest);
    string ignore, command, arg;
    stringstream ss;
    ss << req;
    
    if(req.find(FTP_REQUEST_USER) != string::npos
        || req.find(FTP_REQUEST_PASSWORD) != string::npos
            || req.find(FTP_REQUEST_CWD) != string::npos
                || req.find(FTP_REQUEST_RETR) != string::npos)
    {
        ss >> command;
        strcpy(requestName, command.c_str());
        ss >> arg;
        strcpy(requestArgument, arg.c_str());
    }

    else 

        strcpy(requestName, req.c_str());
}

/** @brief hyandles request user
 *
 *  This function matches the username provided by the client against  
 *  the valid username. Sends a success response if it matches and sends 
 *  an unsuccessful response otherwise.
 *
 *  @param username a character array that holds the username
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */

void handleFtpRequestUSER(const char* username, ClientFtpSession& clientFtpSession)
{
    if(strcmp(username, DEFAULT_USERNAME) == 0)
    {
        clientFtpSession.isValidUser = true;
        int status = sendToRemote(clientFtpSession.controlConnection, USERNAME_OK_RESPONSE, strlen(USERNAME_OK_RESPONSE));
    
        if(status < 0)

            cout << "Encountered an error while sending data\n";
    }

    else
    {
        int status = sendToRemote(clientFtpSession.controlConnection, INVALID_USERNAME_RESPONSE, strlen(INVALID_USERNAME_RESPONSE));
    
        if(status < 0)
        {
            cout << "Encountered an error while sending data\n"; 
        }
	    
        stopClientFTPSession(clientFtpSession);
    }
}

/** @brief handles request pass
 *
 *  This function matches the passord provided by the client against  
 *  the valid password. Sends a success response if it matches and sends 
 *  an unsuccessful response otherwise.
 *
 *  @param password a character array that holds the password
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */

void handleFtpRequestPASS(const char* password, ClientFtpSession& clientFtpSession)
{
    if(clientFtpSession.isValidUser == false)

        handleNotLoggedIn(clientFtpSession);

    else if(strcmp(password, DEFAULT_PASSWORD) != 0)
    
	handleNotLoggedIn(clientFtpSession);

    else 
    {
        clientFtpSession.isLoggedIn = true;

        int status = sendToRemote(clientFtpSession.controlConnection, LOGIN_RESPONSE, strlen(LOGIN_RESPONSE));
    
        if(status < 0)

            cout << "Encountered an error while sending data\n";
    }
}

/** @brief handles request pwd
 *
 *  This function finds the current working direcotry and sends it to the 
 *  client
 *
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */

void handleFtpRequestPWD(ClientFtpSession& clientFtpSession)
{
    char path[256];

    if(clientFtpSession.isLoggedIn == false)

        handleNotLoggedIn(clientFtpSession);

    else
    {
        if(getcwd(path, sizeof(path)) != NULL)
        {
            int status = sendToRemote(clientFtpSession.controlConnection, path, strlen(path));
    
            if(status < 0)

                cout << "Encountered an error while sending data\n";
        }
    }
}

/** @brief handles request cwd
 *
 *  This function changes the current working direcotry to the 
 *  user defined directory if the user defined directory is valid.
 *
 *  @param directory a character array that holds the name of the directory
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */

void handleFtpRequestCWD(const char* directory, ClientFtpSession& clientFtpSession)
{
    
    char dir[strlen(directory) + 1];

    strcpy(dir,directory);

    if(clientFtpSession.isLoggedIn == false)

        handleNotLoggedIn(clientFtpSession);

    else
    {
        if(strstr(dir, "/.") != NULL)
        {
            int status = sendToRemote(clientFtpSession.controlConnection, INVALID_PATH_RESPONSE, strlen(INVALID_PATH_RESPONSE));
    
            if(status < 0)

                cout << "Encountered an error while sending data\n";
        }

        else if(strstr(dir, "/..") != NULL)
        {
            int status = sendToRemote(clientFtpSession.controlConnection, INVALID_PATH_RESPONSE, strlen(INVALID_PATH_RESPONSE));
    
            if(status < 0)

                cout << "Encountered an error while sending data\n";
        }

        else if(strstr(dir, "*") != NULL)
        {
            int status = sendToRemote(clientFtpSession.controlConnection, INVALID_PATH_RESPONSE, strlen(INVALID_PATH_RESPONSE));
    
            if(status < 0)

                cout << "Encountered an error while sending data\n";
        }

        else if(strncmp(dir, PATH_NOT_ALLOWED_CURERENT_DIRECTORY, strlen(PATH_NOT_ALLOWED_CURERENT_DIRECTORY)) == 0)
        {
            int status = sendToRemote(clientFtpSession.controlConnection, INVALID_PATH_RESPONSE, strlen(INVALID_PATH_RESPONSE));
    
            if(status < 0)

                cout << "Encountered an error while sending data\n";
        }

        else if(strncmp(dir, PATH_NOT_ALLOWED_PARENT_DIRECTORY, strlen(PATH_NOT_ALLOWED_PARENT_DIRECTORY)) == 0)
        {
            int status = sendToRemote(clientFtpSession.controlConnection, INVALID_PATH_RESPONSE, strlen(INVALID_PATH_RESPONSE));
    
            if(status < 0)

                cout << "Encountered an error while sending data\n";
        }

        else
        {
            if(chdir(directory) >= 0)
            {
                int status = sendToRemote(clientFtpSession.controlConnection, CHANGE_DIRECTORY_RESPONSE, strlen(CHANGE_DIRECTORY_RESPONSE));
    
                if(status < 0)

                    cout << "Encountered an error while sending data\n";
            }

            else
            {
                int status = sendToRemote(clientFtpSession.controlConnection, CWD_FAIL_RESPONSE, strlen(CWD_FAIL_RESPONSE));
    
                if(status < 0)

                    cout << "Encountered an error while sending data\n";
            }
                
            
        }
    }
}

/** @brief handles request pwd
 *
 *  This function changes the current working direcotry to the  
 *  parent directory if it is within valid bounds
 *
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */

void handleFtpRequestCDUP(ClientFtpSession& clientFtpSession)
{
    char path[256];

    if(clientFtpSession.isLoggedIn == false)

        handleNotLoggedIn(clientFtpSession);

    else
    {
        if(getcwd(path, sizeof(path)) != NULL)
        {
            if(strcmp(path, clientFtpSession.rootDir) == 0)
            {
                int status = sendToRemote(clientFtpSession.controlConnection, CDUP_FAIL_RESPONSE, strlen(CDUP_FAIL_RESPONSE));
    
                if(status < 0)

                    cout << "Encountered an error while sending data\n";
            }

            else
            {
                chdir("..");

                int status = sendToRemote(clientFtpSession.controlConnection, CHANGE_TO_PARENT_DIRECTORY_RESPONSE, strlen(CHANGE_TO_PARENT_DIRECTORY_RESPONSE));
    
                if(status < 0)

                    cout << "Encountered an error while sending data\n";
            }
        }
    }
}

void handleFtpRequestPASV(ClientFtpSession& clientFtpSession)
{
    if(clientFtpSession.isLoggedIn == false)

        handleNotLoggedIn(clientFtpSession);
    
    else 

        enteringIntoPassive(clientFtpSession);
}

void handleFtpRequestNLST(ClientFtpSession& clientFtpSession)
{
    int numEntries;
    char buffer[256]; 

    if(clientFtpSession.isLoggedIn == false)

        handleNotLoggedIn(clientFtpSession);

    else
    {
        if(clientFtpSession.dataConnection < 0)
        {
            int status = sendToRemote(clientFtpSession.controlConnection, DATA_OPEN_CONNECTION_ERROR_RESPONSE, strlen(DATA_OPEN_CONNECTION_ERROR_RESPONSE));
    
            if(status < 0)

                cout << "Encountered an error while sending data\n";
        }

        else
        {
            numEntries = listDirEntries(clientFtpSession.dataConnection);

            sprintf(buffer, NLST_CONNECTION_CLOSE_RESPONSE, numEntries);
            
            int status = sendToRemote(clientFtpSession.controlConnection, buffer, strlen(buffer));
    
            if(status < 0)

                cout << "Encountered an error while sending data\n";

            closeConnection(clientFtpSession.dataConnection);
        }
    }
}

void handleFtpRequestRETR(const char* file, ClientFtpSession& clientFtpSession)
{

}

/** @brief handles request quit
 *
 *  This function quits the client session by closing all the sockets 
 *
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */

void handleFtpRequestQUIT(ClientFtpSession& clientFtpSession)
{
    int status = sendToRemote(clientFtpSession.controlConnection, QUIT_RESPONSE, strlen(QUIT_RESPONSE));
    
        if(status < 0)

            cout << "Encountered an error while sending data\n";

    sleep(3);
    
    stopClientFTPSession(clientFtpSession);
}

/** @brief handles unsupported request
 *
 *  This function handles unsupported commands by sending approprtiate
 *  response to client
 *
 *  @param clientFtpSession an object of type clientFtpSession to hold session status data
 */

void handleFtpRequestUnSupported(ClientFtpSession& clientFtpSession)
{
    int status = sendToRemote(clientFtpSession.controlConnection, UNSUPPORTED_COMMAND_RESPONSE, strlen(UNSUPPORTED_COMMAND_RESPONSE));
    
    if(status < 0)

        cout << "Encountered an error while sending data\n";
}

void handleNotLoggedIn(ClientFtpSession& clientFtpSession)
{
    int status = sendToRemote(clientFtpSession.controlConnection, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));
    
    if(status < 0)

        cout << "Encountered an error while sending data\n";

    sleep(3);
    
    stopClientFTPSession(clientFtpSession);
}

