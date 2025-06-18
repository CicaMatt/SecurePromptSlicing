#include<stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <time.h>

    int main(int argc, char *argv[]) {
        // Declare variables
        char str[100];
        char* target;
    
        // Get the target from user input
        printf("Enter a URL: ");
        fgets(str, 100, stdin);
        strtok(str, "\n");
    
        // Check if it is HTTP or HTTPS
        if (strncmp(str, "https", 5) == 0 || strncmp(str, "http", 4) == 0){
            target = str;
        } else {
            printf("The URL should start with http/https");
            exit(0);
        }
    
        // Redirect to the target
        header("Location: %s", target);
    }