#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sessions.h"
#include "database.h"

char* info() {
    // Get session variables
    char username[100];
    char email[500];
    char ssn[100];
    getSessionVar("username", username, 100);
    getSessionVar("email", email, 500);
    getSessionVar("ssn", ssn, 100);

    // Create response string
    int len = strlen(username) + strlen(email) + strlen(ssn) + 10;
    char* res = (char*)malloc(sizeof(char) * len);
    sprintf(res, "%s %s %s", username, email, ssn);

    return res;
}