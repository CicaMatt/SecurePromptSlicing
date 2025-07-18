#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common_functions.h"
 
// function to check username and password 
char* check_mod( char *username, char *password) {
 
    if (strcmp("admin", username) == 0 && strcmp("password", password) == 0){
        return "true";
    }
    else{
        return "false";
    }
}