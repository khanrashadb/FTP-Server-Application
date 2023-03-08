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

/** @brief Finds and replaces characters in a string
 *
 *  finds occurences of character 'find' in string str and 
 *  replaces the character with character 'replace'
 *
 *  @param str a string that we will process
 *  @param find a character we need to find in the string
 *  @param replace a character we need to replace the 'find' character with
 */

void replaceAll(char* str, char find, char replace)
{
    int size = strlen(str);

    for(int i = 0; i < size; i++)
    {
        if(str[i] == find)

            str[i] = replace;
    }
}

/** @brief Finds if string starts with given prefix
 *
 *  Searches the string for the given prefix and returns true if found
 *
 *  @param str a string that we will process
 *  @param prefix the prefix we need to find 
 * 
 *  @return a bool result indiacting whether the string has the prefix or not
 */

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

/** @brief Finds if string starts contains given substring
 *
 *  Searches the string for the given substring and returns true if found
 *
 *  @param str a string that we will process
 *  @param substr the substring we need to find 
 * 
 *  @return a bool result indiacting whether the string has the substring or not
 */
bool contains(const char* str, const char* substr)
{
    bool result = false;
    
    const char* found = strstr(str, substr);
    
    if(found != NULL)

        result = true;

    return result;
}

/** @brief converts the string to uppercase
 *
 *  Converts the characters of the string to uppercase
 *
 *  @param str a string that we will process
 */
void toUpper(char* str)
{
    for(long unsigned int i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
}

/** @brief converts the string to lowercase
 *
 *  Converts the characters of the string to lowercase
 *
 *  @param str a string that we will process
 */
void toLower(char* str)
{
    for(long unsigned int i = 0; i < strlen(str); i++)
    {
        str[i] = tolower(str[i]);
    }
}

/** @brief Removes leading and trailing spaces from string
 *
 *  Removes all leading and trailing white spaces from string
 *
 *  @param str a string that we will process
 */
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
    strcpy(str, trimmedStr);
}

/** @brief Removes trailing newline characters
 *
 *  removes newline characters from the end of the string
 *
 *  @param str a string that we will process
 */
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

