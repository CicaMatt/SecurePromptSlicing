#include <string.h>
#include <stdio.h>

int main() {
    char name[256], password[256];
    printf("Enter your name: ");
    scanf("%s", &name);
    printf("\nEnter a password: ");
    scanf("%s", &password);
    unsigned long long int hashed_password = 0;
    for (int i = 0; i < strlen(password); i++) {
        hashed_password += password[i] + name[i];
    }
    printf("\nYour hashed password is: %llu", hashed_password);
    return 0;
}