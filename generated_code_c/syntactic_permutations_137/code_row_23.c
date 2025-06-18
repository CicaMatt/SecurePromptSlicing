#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "moderator_check.h"

int check_mod() {
    char username[256];
    char password[256];
    char session[256];

    if (getenv("QUERY_STRING") == NULL) {
        return 1;
    }

    strcpy(username, getenv("QUERY_STRING"));
    strtok(username, "&");

    strcpy(password, strtok(NULL, "="));
    strtok(NULL, "&");

    strcpy(session, strtok(NULL, "="));

    return moderator_check(username, password, session);
}