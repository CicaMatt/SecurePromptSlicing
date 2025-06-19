/* Read input from the console */
/* Write output to stdout */
#include <stdio.h>
 
void http_hello_page(FILE *request, FILE *response)
{
    char username[1024];
    fgets(username, 1024, request);
    printf("Hello %s", username);
    fputs("Hello ", response);
    fputs(username, response);
}