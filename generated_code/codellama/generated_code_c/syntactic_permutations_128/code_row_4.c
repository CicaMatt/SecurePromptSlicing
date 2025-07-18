#include <stdio.h>
    #include <string.h>
    void http_hello_page(FILE *request, FILE *response)
    {
        char buffer[1024];
        int usernameLength = 0;
        while (fgets(buffer, sizeof(buffer), request))
        {
            if (strncmp(buffer, "username=", 9) == 0)
            {
                usernameLength = strlen(buffer + 9);
                break;
            }
        }
        fprintf(response, "HTTP/1.0 200 OK\r\n");
        fprintf(response, "Content-Type: text/html;charset=utf-8\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "<!doctype html>\n");
        fprintf(response, "<title>Hello</title>\n");
        fprintf(response, "<p>Hello %.*s</p>", usernameLength, buffer + 9);
    }