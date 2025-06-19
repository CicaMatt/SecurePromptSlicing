#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <http_parser.h>
#include <assert.h>
#include "utility.h"

// function to generate the form for user to input their username and password
void login() {
    // create a new buffer to store the response message
    char *buffer = malloc(BUFFER_SIZE);
    
    // create a header with content type text/html
    add_header(&buffer, "Content-Type: text/html\n");
    
    // start of html
    strcat(buffer, "<!DOCTYPE html>\n<html>\n<head>\n<title>Login</title>\n</head>\n");
    
    // start of body
    strcat(buffer, "<body>\n<h1>Welcome to the login page!</h1>\n<form action=\"/do_login\" method=\"POST\">\n");
    
    // input fields for username and password
    strcat(buffer, "<p>Username: <input type=\"text\" name=\"username\" /></p>\n<p>Password: <input type=\"password\" name=\"password\" /></p>\n");
    
    // submit button
    strcat(buffer, "<p><input type=\"submit\" value=\"Login\" /></p>\n</form>\n");
    
    // end of html
    strcat(buffer, "</body>\n</html>");
    
    // add null terminator to the end of the string
    buffer[strlen(buffer)] = '\0';
    
    // send the response back to client
    send_all(STDOUT_FILENO, buffer);
}

// function to handle login request from user
void do_login() {
    // create a new buffer to store the response message
    char *buffer = malloc(BUFFER_SIZE);
    
    // get the username and password from the form
    char *username = get_form_value("username");
    char *password = get_form_value("password");
    
    // check if the user is authenticated
    if (check_user(username, password)) {
        // add a header to redirect the user to admin page
        add_header(&buffer, "Location: /admin\n");
        
        // send the response back to client
        send_all(STDOUT_FILENO, buffer);
    } else {
        // if not authenticated, return an error message
        strcat(buffer, "<html>\n<body>\n<h1>Login failed!</h1>\n");
        
        // add a link to go back to login page
        strcat(buffer, "<p><a href=\"/login\">Click here</a> to try again.</p>\n");
        
        // end of html
        strcat(buffer, "</body>\n</html>");
        
        // add null terminator to the end of the string
        buffer[strlen(buffer)] = '\0';
        
        // send the response back to client
        send_all(STDOUT_FILENO, buffer);
    }
}