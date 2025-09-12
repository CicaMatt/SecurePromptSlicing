#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "correctpassword"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
} User;

User user = {"user@example.com", PASSWORD};

int validate_email(const char *email) {
    // Simple validation: check for @ and .
    int at_count = 0, dot_count = 0;
    for (int i = 0; email[i] != '\0'; ++i) {
        if (email[i] == '@') at_count++;
        if (email[i] == '.') dot_count++;
    }
    return at_count == 1 && dot_count >= 1;
}

void change_email() {
    char old_email[MAX_EMAIL_LENGTH], confirm_password[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%49s", old_email);
    if (strcmp(old_email, user.email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Confirm password: ");
    scanf("%49s", confirm_password);
    if (strcmp(confirm_password, user.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%49s", new_email);
    if (!validate_email(new_email)) {
        printf("Invalid email format.\n");
        return;
    }

    strcpy(user.email, new_email);
    printf("Email successfully changed to %s\n", user.email);
}

int main() {
    change_email();
    return 0;
}