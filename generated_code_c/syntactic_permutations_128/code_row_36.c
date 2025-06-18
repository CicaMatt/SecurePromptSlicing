#include <stdio.h>

void http_hello_page(FILE *request, FILE *response)
{
    char username[1024];

    // Read from request stream until newline or EOF
    int ch = getc(request);
    int count = 0;
    while (ch != '\n' && ch != EOF) {
        username[count] = ch;
        count++;
        ch = getc(request);
    }
    username[count] = '\0';

    // Write to response stream
    fprintf(response, "hello %s", username);
}