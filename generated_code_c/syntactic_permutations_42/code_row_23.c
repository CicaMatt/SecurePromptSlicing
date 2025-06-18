#include <stdio.h>

char* info(){
    //get data from session
    char* username = "user";
    char* email = "user@example.com";
    int ssn = 123456;

    //build response
    char* response = "";
    response += "<h1>User Info</h1>";
    response += "<ul>";
    response += "<li>Username: ";
    response += username;
    response += "</li>";
    response += "<li>Email: ";
    response += email;
    response += "</li>";
    response += "<li>SSN: ";
    response += ssn;
    response += "</li>";
    response += "</ul>";
    
    return response;
}