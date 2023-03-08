/**
 * @file ftp_server_string_util.cpp
 * @author Rashad Khan, 658285853, S23N02, CSCI 460, VIU
 * @version 1.0.0
 * @date March 08, 20213
 *
 * Contains the function descriptions of the prototypes found in "ftp_server_string_util.h" file
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "ftp_server_string_util.h"

using namespace std;

void replaceAll(char* str, char find, char replace)
{
    int size = strlen(str);

    for(int i = 0; i < size; i++)
    {
        if(str[i] == find)

            str[i] = replace;
    }
}

bool startsWith(const char* str, const char* prefix)
{
    bool result = true;
    int prefixSize = strlen(prefix);

    for(int i = 0; i < prefixSize; i++)
    {
        if(str[i] != prefix[i])

            result = false;
    }

    return result;
}

bool contains(const char* str, const char* substr)
{
    bool result = false;
    
    const char* found = strstr(str, substr);
    
    if(found != NULL)

        result = true;

    return result;
}

void toUpper(char* str)
{
    for(long unsigned int i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
}

void toLower(char* str)
{
    for(long unsigned int i = 0; i < strlen(str); i++)
    {
        str[i] = tolower(str[i]);
    }
}

void stripLeadingAndTrailingSpaces(char* str)
{
    int size = strlen(str);
    char trimmedStr[size];

    // Removing trailing spaces

    int i = size - 1;

    while(i >= 0)
    {
        if(str[i] != ' ') // Finding the last index from the end of the string which has a character other than a white space

            break;

        i--;
    }

    if(i != size - 1)     // If the string has trailing spaces then we terminate the string earlier.

        str[i + 1] = '\0';

    // Removing leading white spaces

    int startingIndex = 0;

    while(startingIndex < i + 1)
    {
        if(str[startingIndex] != ' ')
        
            break;

        else

            startingIndex++;
    }

    for(int j = startingIndex; j < i + 1; j++)
    {
        trimmedStr[j - startingIndex] = str[j];
    }

    trimmedStr[i+1] = '\0';
}

void stripNewlineAtEnd(char* str)
{
    int i = 1;

    while(str[strlen(str) - i] == '\n' && (strlen(str) - i) >= 0)
    {
        i++;
    }

    i--;

    str[strlen(str) - i] = '\0';
}

