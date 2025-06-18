#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void main() {
     char username[20];
     char password[20];

     printf("Enter Username: ");
     scanf("%s", &username);
     printf("Enter Password: ");
     scanf("%s", &password);
     if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
       printf("Login Successful\n");
     } else {
       printf("Invalid Credentials\n");
     }
    }