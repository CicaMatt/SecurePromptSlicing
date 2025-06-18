#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

char username[128] = {0};
char password[128] = {0};
int valid_login = 0;

void do_login(){
    char *user, *pass;

    user = getenv("QUERY_STRING");
    if(user == NULL){
        printf("<h2>Error: No QUERY_STRING set</h2>\n");
        return;
    }

    pass = strchr(user, '=');
    if(pass == NULL){
        printf("<h2>Error: Invalid login credentials</h2>\n");
        return;
    }
    *pass = 0;
    pass++;

    if(strcmp(user, username) || strcmp(pass, password)){
        printf("<h2>Error: Invalid login credentials</h2>\n");
        return;
    }
    
    valid_login = 1;
}

int main(){
    char *page, *secret_page;

    page = "/index.html";
    secret_page = "/secret.html";

    if(getenv("REQUEST_METHOD") != NULL){
        do_login();
    }

    if(!valid_login && strcmp(page, "/index.html")){
        printf("<h2>Please login</h2>\n");
        return 0;
    }
    
    // output the page
    int fd = open(page, O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(-1);
    }
    
    char buffer[4096];
    ssize_t bytes_read;
    while((bytes_read = read(fd, buffer, sizeof(buffer))) > 0){
        printf("%.*s", (int)bytes_read, buffer);
    }
    close(fd);
    
    return 0;
}