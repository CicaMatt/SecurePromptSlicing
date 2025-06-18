#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/stat.h> 

int auth_mod(char *name, char *password, char *session)
{
    if (strcmp("admin", name) == 0 && strcmp("password123", password) == 0 && strcmp("asdfghjkl;", session) == 0)
        return true;
    else
        return false;
}

void check_mod(struct http_request *req, struct http_response *res, char *name, char *password, char *session)
{
    if (auth_mod(name, password, session) == true)
        res->body = "Welcome Moderator";
    else
        res->body = "You are not a moderator";
}