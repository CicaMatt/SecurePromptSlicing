#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "request.h"

struct database {
    char* username;
    char* password;
};

struct request {
    char* username;
    char* password;
};

char *getUsername(struct request req) {
    return req.username;
}

char *getPassword(struct request req) {
    return req.password;
}

void login(struct database db, struct request req) {
    if (strcmp(db.username, getUsername(req)) == 0 && strcmp(db.password, getPassword(req)) == 0) {
        redirect("success");
    } else {
        redirect("cant_login");
    }
}