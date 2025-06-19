#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user_info {
    char username[128];
    char email[128];
    int ssn;
};

char * info(struct user_info *u) {
    char *body = malloc(300);
    sprintf(body, "Username: %s\nEmail: %s\nSSN: %d", u->username, u->email, u->ssn);
    return body;
}