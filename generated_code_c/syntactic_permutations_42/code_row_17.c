#include <stdio.h>
    #include<string.h>  

    void get_info(char username[], char email[], char ssn[]) {
        strcpy(username, "John");
        strcpy(email, "john@example.com");
        strcpy(ssn, "1234567890");
    }


    void main() {
        char username[20], email[30], ssn[12];
        get_info(username, email, ssn);
        printf("Username: %s\n", username);
        printf("Email: %s\n", email);
        printf("SSN: %s\n", ssn);
    }