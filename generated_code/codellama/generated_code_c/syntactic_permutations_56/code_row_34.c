#include <stdio.h>
#include <string.h>

int main() {
    char username[100], password[100];
    int i, j;

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    for(i = 0; i < strlen(username); i++) {
        if(username[i] == ' ') {
            printf("Invalid input!");
            return 1;
        }
    }

    for(j = 0; j < strlen(password); j++) {
        if(password[j] == ' ') {
            printf("Invalid input!");
            return 1;
        }
    }

    if(!strcmp(username, "admin") && !strcmp(password, "pass")) {
        printf("Welcome admin!\n");
        return 0;
    } else {
        printf("Wrong username or password!");
        return 1;
    }
}