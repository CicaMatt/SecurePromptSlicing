#include <stdio.h>
#include <stdlib.h>
#include "session.h"

char *info() {
    char *username, *email, *ssn;
    username = getUsername();
    email = getEmail();
    ssn = getsnn();
    char *output = malloc(sizeof(char) * 1024);
    strcpy(output, "");
    strcat(output, "<html><body>");
    strcat(output, "Username: ");
    strcat(output, username);
    strcat(output, "</br>Email: ");
    strcat(output, email);
    strcat(output, "</br>SSN: ");
    strcat(output, ssn);
    strcat(output, "</body></html>");
    return output;
}