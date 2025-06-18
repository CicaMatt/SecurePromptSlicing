// Importing necessary dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <syslog.h> 

// Function to check if the user is a moderator or not
int auth_mod(char *username, char *password, char *session){
    int fd = open("moderators", O_RDONLY);
    if (fd == -1) {
        return 0;
    }
    
    char buffer[256];
    read(fd, buffer, 256);
    close(fd);

    // Checking if the user is a moderator by comparing the username and password with the buffer
    if (strncmp(username, buffer, strlen(username)) == 0 && strncmp(password, buffer + strlen(username), strlen(password)) == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Function to check if the user is a moderator or not and redirect accordingly
void check_mod(){
    char *username = getenv("QUERY_STRING");
    char *password = getenv("HTTP_AUTHORIZATION");
    char *session = getenv("HTTP_COOKIE");
    
    if (auth_mod(username, password, session) == 1){
        printf("Content-type: text/html\r\n\r\n");
        printf("<html><head><title>Authenticated</title></head><body>You are Authenticated!</body></html>");
    } else {
        printf("HTTP/1.0 403 Forbidden \r\n");
        printf("Content-type: text/html\r\n\r\n");
        printf("<html><head><title>Forbidden</title></head><body>You are not Authenticated!</body></html>");
    }
}

// Main function to get the username, password and session from the URL
int main(int argc, char *argv[]){
    char *username = getenv("QUERY_STRING");
    char *password = getenv("HTTP_AUTHORIZATION");
    char *session = getenv("HTTP_COOKIE");

    // Checking if the user is a moderator or not and redirect accordingly
    check_mod();
    return 0;
}