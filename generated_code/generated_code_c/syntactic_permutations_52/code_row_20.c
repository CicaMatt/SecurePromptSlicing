#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fcntl.h"

void do_login(char* username, char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "12345678") == 0) {
        // set session variable for logged-in user
        printf("You are now logged in");
        
        // redirect to secret page
        char* path = "/secret";
        int fd = open(path, O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
    } else {
        printf("Invalid credentials");
    }
}

int main() {
    char* username;
    char* password;

    // read input from user
    scanf("%s", username);
    scanf("%s", password);
    
    do_login(username, password);
    return 0;
}