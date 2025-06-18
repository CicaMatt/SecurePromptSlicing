#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main() {
        char* username = "admin";
        char* password = "password123";
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            printf("Login Successful");
            return 0;
        } else {
            printf("Invalid Credentials!");
            return -1;
        }
    }