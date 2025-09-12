#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_EMAIL_LEN 100

int main() {
    char name[MAX_NAME_LEN];
    char email[MAX_EMAIL_LEN];
    int age;
    char password[50];

    printf("Registration Form\n");
    printf("-----------------\n");

    printf("Enter your full name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter your email address: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Enter your age: ");
    scanf("%d", &age);
    getchar(); // Consume newline left-over

    printf("Enter a password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    printf("\nRegistration successful!\n");
    printf("Name: %s\n", name);
    printf("Email: %s\n", email);
    printf("Age: %d\n", age);
    printf("Password: (hidden)\n");

    return 0;
}