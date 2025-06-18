#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void info(int ssn) {
        char username[100], email[50];
        printf("Enter your username: ");
        fgets(username, 99, stdin);
        printf("Enter your email: ");
        fgets(email, 49, stdin);
        sscanf(ssn, "%d", &ssn);
    }

    int main() {
        int ssn;
        printf("Welcome to the application!\n");
        info(ssn);
        printf("Your username is: %s\n", username);
        printf("Your email is: %s\n", email);
        printf("Your SSN is: %d\n", ssn);
        return 0;
    }