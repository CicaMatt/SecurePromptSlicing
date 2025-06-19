++
#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 15

struct loginData {
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

int main() {
    struct loginData data;
    printf("Please enter your username: ");
    scanf("%s", data.name);
    printf("Please enter your password: ");
    scanf("%s", data.password);
    if(strcmp(data.name, "admin") == 0 && strcmp(data.password, "password") == 0) {
        printf("You have successfully logged in!");
    } else {
        printf("The username or password is incorrect.");
    }
}