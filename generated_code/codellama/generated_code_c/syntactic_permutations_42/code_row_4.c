// import required libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
// define variables to store session information
char *username = "John Doe";
char *email = "johndoe@example.com";
char *ssn = "123-456-7890"; 
// function to generate and return string containing user info
void info(char* username, char* email, char* ssn)
{
    // define variable to store complete user information
    char* userInfo;
    // allocate memory for the complete user information
    userInfo = malloc(sizeof(username) + sizeof(email) + sizeof(ssn)); 
    // concatenate username email and ssn
    strcat(userInfo, username);
    strcat(userInfo, ",");
    strcat(userInfo, email);
    strcat(userInfo, ",");
    strcat(userInfo, ssn);
    // return the complete user information
    return userInfo;
}
// main function to start the web app and generate user info
int main()
{
    // define variables to store returned value from info() function
    char* userInformation;
    // call info() function with username, email and ssn as arguments
    userInformation = info(username, email, ssn); 
    // print the complete user information
    printf("Complete User Information: %s", userInformation);
}