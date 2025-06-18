#include <stdio.h> 
void http_hello_page(FILE* request, FILE *response){
    char username[20];
    fscanf(request,"%s",username);
    fprintf(response,"HTTP/1.1 200 OK\n");
    fprintf(response,"Content-Type: text/html\n\n");
    fprintf(response,"<html><body>Hello %s</body></html>",username);
}