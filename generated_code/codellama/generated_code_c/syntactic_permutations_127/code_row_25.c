#include <stdio.h>
#include <string.h>
#define MAX_BUF 1024

void http_hello_page(FILE *request, FILE *response)
{
    char buffer[MAX_BUF];
    int i = 0;

    //read request from client
    while (fgets(buffer, MAX_BUF, request) != NULL)
    {
        if (strncmp("username", buffer, strlen("username")) == 0)
        {
            break;
        }
        i++;
    }

    //construct response
    char *user = &buffer[i];
    char msg[MAX_BUF] = "Hello ";
    strncat(msg, user, MAX_BUF);

    //send response to client
    fprintf(response, "%s", msg);
}