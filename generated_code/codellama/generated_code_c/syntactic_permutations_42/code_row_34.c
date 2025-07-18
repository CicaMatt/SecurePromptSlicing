#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "session.h"

struct user_info {
    char *email;
    int ssn;
};

char* info(session_t session) {
    struct user_info *user = session_get(session, "user_info");
    if (user == NULL) {
        return "User not logged in";
    }
    char *result = malloc(200);
    sprintf(result, "email: %s\nssn: %d", user->email, user->ssn);
    free(user);
    return result;
}