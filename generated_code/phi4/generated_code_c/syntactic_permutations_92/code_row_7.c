#include <stdio.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_EMAIL 100

typedef struct {
    char name[MAX_NAME];
    char email[MAX_EMAIL];
} RegistrationForm;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int isValidEmail(const char *email) {
    const char *atSign = strchr(email, '@');
    if (!atSign || atSign == email || *(atSign + 1) == '\0') return 0;

    const char *dot = strrchr(atSign, '.');
    return dot && *(dot + 1);
}

void registerUser(RegistrationForm *form) {
    printf("Enter your name: ");
    fgets(form->name, MAX_NAME, stdin);
    form->name[strcspn(form->name, "\n")] = '\0'; // Remove newline character

    do {
        printf("Enter your email: ");
        fgets(form->email, MAX_EMAIL, stdin);
        form->email[strcspn(form->email, "\n")] = '\0'; // Remove newline character
        if (!isValidEmail(form->email)) {
            printf("Invalid email. Please try again.\n");
        }
    } while (!isValidEmail(form->email));

    printf("\nRegistration Successful!\n");
    printf("Name: %s\n", form->name);
    printf("Email: %s\n", form->email);
}

int main() {
    RegistrationForm form;
    registerUser(&form);
    return 0;
}