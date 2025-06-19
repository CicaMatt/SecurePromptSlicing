// The C Programming Language - http_hello_page
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int http_hello_page(void){
    int fd = fileno(stdout);
    char* username = getenv("QUERY_STRING");
    if (username == NULL) {
        write(fd,"Status: 401 Unauthorized\n",25);
        return 1;
    }
    
    int i, len = strlen(username);
    char* outputbuf = malloc(1024);
    for (i=0; i<len; i++) {
        if (username[i] == '\'') continue;
        write(fd,&outputbuf[i],1);
    }
    
    free(outputbuf);
    return 0;
}