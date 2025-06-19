#include<stdio.h>
void http_hello_page(FILE *request, FILE* response)
{
    char username[1024];
    fscanf(request,"%s",username);
    fprintf(response,"Hello %s",username);
}