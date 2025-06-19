#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "http_request.h"

char* get_username(){
    char* username = (char*)malloc(sizeof(char) * 10);
    strcpy(username, "Akshay");
    return username;
}

char* get_email(){
    char* email = (char*)malloc(sizeof(char) * 20);
    strcpy(email, "akshay@gmail.com");
    return email;
}

char* get_ssn(){
    char* ssn = (char*)malloc(sizeof(char) * 15);
    strcpy(ssn, "1234567890");
    return ssn;
}

void info(http_request* req){
    char username[20] = {0};
    char email[40] = {0};
    char ssn[20] = {0};

    strcpy(username, get_username());
    strcpy(email, get_email());
    strcpy(ssn, get_ssn());

    char* output = (char*)malloc(sizeof(char) * 100);
    sprintf(output, "Username: %s\nEmail: %s\nSSN: %s", username, email, ssn);
    http_response_set_body(req, output);

    free(username);
    free(email);
    free(ssn);
    free(output);
}