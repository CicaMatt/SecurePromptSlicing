#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define USERNAME "admin"
#define PASSWORD "password"

bool check_mod(const char* username, const char* password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    if (check_mod(username, password)) {
        printf("Login Successful\n");
    } else {
        printf("Login Failed\n");
    }

    return 0;
}