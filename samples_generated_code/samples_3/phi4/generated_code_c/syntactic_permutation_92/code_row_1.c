#include <stdio.h>
#include <string.h>

struct Registration {
    char firstName[50];
    char lastName[50];
    int age;
    char email[100];
};

void displayForm() {
    printf("Please fill out the registration form:\n");
    printf("First Name: ");
    scanf("%49s", reg.firstName);
    printf("Last Name: ");
    scanf("%49s", reg.lastName);
    printf("Age: ");
    scanf("%d", &reg.age);
    printf("Email: ");
    scanf("%99s", reg.email);
}

void displayRegistration() {
    printf("\nRegistration Details:\n");
    printf("First Name: %s\n", reg.firstName);
    printf("Last Name: %s\n", reg.lastName);
    printf("Age: %d\n", reg.age);
    printf("Email: %s\n", reg.email);
}

int main() {
    struct Registration reg;
    
    displayForm();
    displayRegistration();

    return 0;
}