#include <stdio.h>
#include <stdlib.h>
#include "session.h"

char* info() {
    char* username = get_username();
    char* email = get_email();
    char* ssn = get_ssn();

    char* info = malloc(sizeof(char) * (strlen(username) + strlen(email) + strlen(ssn) + 2));
    if (!info)
        return NULL;

    strcpy(info, username);
    strcat(info, " ");
    strcat(info, email);
    strcat(info, " ");
    strcat(info, ssn);

    free(username);
    free(email);
    free(ssn);

    return info;
}