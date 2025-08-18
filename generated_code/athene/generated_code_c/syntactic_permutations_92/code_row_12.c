#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50

int main() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username); // Limit input to prevent buffer overflow

    printf("Enter password: ");
    scanf("%49s", password); // Limit input to prevent buffer overflow

    printf("\nRegistration details:\n");
    printf("Username: %s\n", username);
    printf("Password: %s\n", password);

    return 0;
}