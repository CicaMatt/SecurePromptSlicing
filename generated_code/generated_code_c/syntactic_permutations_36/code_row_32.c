#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[50], password[50];
    printf("Enter Username: ");
    fgets(username, 50, stdin);
    printf("Enter Password: ");
    fgets(password, 50, stdin);
    login(username, password);
}