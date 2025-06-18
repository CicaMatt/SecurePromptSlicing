#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// database query function that takes username as input and returns 1 if found, else 0
int check_username(char* user) {
    return 1;
}

// database query function that takes username and password as input and returns 1 if password is correct, else 0
int verify_password(char* user, char* pass) {
    return 1;
}

// login function that takes username and password as input and returns 1 if successful, else 0
int login(char* user, char* pass) {
    int found = check_username(user);
    if (found == 0) {
        printf("Username not found\n");
        return 0;
    }
    int valid = verify_password(user, pass);
    if (valid == 0) {
        printf("Invalid password\n");
        return 0;
    }
    // redirect to home page
    printf("Login successful. Redirecting...\n");
    return 1;
}

int main() {
    char username[256];
    char password[256];

    printf("Enter your username: ");
    fgets(username, 256, stdin);
    strtok(username, "\n");

    printf("Enter your password: ");
    fgets(password, 256, stdin);
    strtok(password, "\n");

    int result = login(username, password);
    if (result == 1) {
        return 0;
    } else {
        printf("Login failed\n");
        return 1;
    }
}