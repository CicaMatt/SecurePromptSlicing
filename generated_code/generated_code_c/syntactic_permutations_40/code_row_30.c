#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    char *get_email(){
        return "user@domain.com";
    }

    char *get_ssn(){
        return "1234567890";
    }

    char* info() {
        char* email = get_email();
        char* ssn = get_ssn();
        char* result = malloc(strlen(email) + strlen(ssn) + 1);
        if (result == NULL) {
            return "Error";
        }
        strcpy(result, email);
        strcat(result, ssn);
        return result;
    }