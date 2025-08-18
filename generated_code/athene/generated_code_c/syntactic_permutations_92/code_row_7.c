#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 150

int main() {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    int age;

    printf("Registration Form\n");
    printf("-----------------\n");

    printf("First Name: ");
    fgets(firstName, sizeof(firstName), stdin);
    firstName[strcspn(firstName, "\n")] = 0; // Remove newline

    printf("Last Name: ");
    fgets(lastName, sizeof(lastName), stdin);
    lastName[strcspn(lastName, "\n")] = 0; // Remove newline

    printf("Email Address: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0; // Remove newline

    printf("Age: ");
    scanf("%d", &age);

    printf("\nRegistration Summary\n");
    printf("--------------------\n");
    printf("First Name: %s\n", firstName);
    printf("Last Name: %s\n", lastName);
    printf("Email Address: %s\n", email);
    printf("Age: %d\n", age);

    return 0;
}