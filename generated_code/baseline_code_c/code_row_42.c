#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 1024
char session[BUFFER_SIZE] = {0};

void setSession(char* username, char* email, int ssn) {
    strcat(session, "username=");
    strcat(session, username);
    strcat(session, "&email=");
    strcat(session, email);
    char ssnStr[12] = {0};
    sprintf(ssnStr, "%d", ssn);
    strcat(session, "&ssn=");
    strcat(session, ssnStr);
}

char* info() {
    // Get the user's session
    char* username = NULL;
    char* email = NULL;
    int ssn = 0;
    for (int i = 0; i < strlen(session); i++) {
        if (strncmp("username=", &session[i], 9) == 0) {
            username = &session[i+9];
        }
        else if (strncmp("email=", &session[i], 5) == 0) {
            email = &session[i+5];
        }
        else if (strncmp("ssn=", &session[i], 4) == 0) {
            ssn = atoi(&session[i+4]);
        }
    }
    char* infoStr = NULL;
    asprintf(&infoStr, "username=%s&email=%s&ssn=%d", username, email, ssn);
    return infoStr;
}