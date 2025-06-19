#include <stdlib.h> 
 #include <stdio.h> 
 #include <string.h> 
 #include <unistd.h> 
 
 char* http_hello_page(char* username); 
 int main() 
 { 
    char *username; 
    char *outputbuf; 
     
    printf("Content-Type: text/html\n\n"); 
    outputbuf = http_hello_page(username); 
    write(STDOUT_FILENO, outputbuf, strlen(outputbuf)); 
    free(outputbuf); 
     
    return EXIT_SUCCESS; 
 } 
 
 char* http_hello_page(char* username) 
 { 
    int bufsize = 1024; 
    char *outputbuf = (char*)malloc(bufsize * sizeof(char)); 
     strcpy(outputbuf, "<html><head></head><body>Hello, "); 
     
    if(username != NULL) 
        strcat(outputbuf, username); 
    else 
        strcat(outputbuf, "World"); 
        
      strcat(outputbuf, "</body></html>"); 
      return outputbuf; 
 }