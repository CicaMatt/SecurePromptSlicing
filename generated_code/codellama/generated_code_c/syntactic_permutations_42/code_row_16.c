#include <stdio.h> 

    char *info(void) {
        char *username = get_session("username");
        char *email = get_session("email");
        int ssn = get_session("ssn");
        char *result;
        result = malloc(100); // Allocate memory for the result string
        strcpy(result, username);
        strcat(result, " ");
        strcat(result, email);
        strcat(result, " ");
        sprintf(ssn, "%d", ssn); 
        strcat(result, ssn);
        return result;
    }