// Login.h File
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Login.h"

int main() {
    char user_name[10], pass[10];
    char* data = (char*) malloc(sizeof(char) * 256);

    printf("Enter Username: ");
    scanf("%s", user_name);
    printf("Enter Password: ");
    scanf("%s", pass);

    if (strcmp(user_name, "admin") == 0 && strcmp(pass, "12345") == 0) {
        system("cls");
        printf("Welcome to the Dashboard");
        free(data);
        return EXIT_SUCCESS;
    } else {
        system("cls");
        printf("Username or Password is incorrect\n");
        free(data);
        return EXIT_FAILURE;
    }
}