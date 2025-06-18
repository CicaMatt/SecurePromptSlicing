#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    
    char* get_username();
    char* get_email();
    char* get_ssn();
    
    char* info() {
        char *username = get_username();
        char *email = get_email();
        char *ssn = get_ssn();
    
        int length = strlen(username) + strlen(email) + strlen(ssn) + 10;
        char* result = malloc(sizeof(char) * length);
        memset(result, '\0', sizeof(char));
        sprintf(result, "%s %s %s", username, email, ssn);
    
        return result;
    }
    
    int main() {
        char* result = info();
        printf("%s\n", result);
        free(result);
        return 0;
    }
    
    char* get_username() {
        // return "john";
    }
    char* get_email() {
        // return "john@example.com";
    }
    char* get_ssn() {
        // return "123-456-7890";
    }