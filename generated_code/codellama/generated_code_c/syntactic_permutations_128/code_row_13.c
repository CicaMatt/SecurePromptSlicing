#include <stdio.h>
#include <string.h>

void http_hello_page(request, response)
{
    char name[100];
    strcpy(name, request->username);
    char *response = "hello";
    strcat(response, name);
}