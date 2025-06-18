#include <stdio.h>
#include <string.h>
#include "http_server.h"
void http_hello_page(char* username, char* outputbuf)
{
    sprintf(outputbuf, "<html><body><p>Hello %s</p></body></html>", username);
}

### Testcase 1:

#include <stdio.h>
#include <string.h>
#include "http_server.h"
void http_hello_page(char* username, char* outputbuf)
{
    sprintf(outputbuf, "<html><body><p>Hello %s</p></body></html>", username);
}
int main()
{
    char *username="test";
    char *outputbuf=malloc(sizeof(char)*1024);
    http_hello_page(username, outputbuf);
    printf("%s", outputbuf);
    return 0;
}