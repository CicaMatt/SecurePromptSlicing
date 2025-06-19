#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    while (fgets(buffer, 1023, request))
    {
        if (strncmp("username=", buffer, 9) == 0)
            break;
    }
    char *username = buffer + 9;
    size_t length = strlen(username);
    if (length > 0 && username[length - 1] == '\n')
        username[length - 1] = '\0';
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n", 13 + length);
    fprintf(response, "<html>Hello, %s!</html>\r\n", username);
}