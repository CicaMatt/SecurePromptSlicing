#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASS_LEN 20

typedef struct {
    char username[MAX_EMAIL_LEN];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];
} User;

User logged_in_user = {"user1", "user1@example.com", "securepass"};

int validate_email(const char *email) {
    int at_count = 0;
    for (int i = 0; email[i]; ++i) {
        if (email[i] == '@') at_count++;
    }
    return (at_count == 1 && strlen(email) > 5);
}

void change_email() {
    char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN], password[MAX_PASS_LEN];

    printf("Enter your current email: ");
    scanf("%49s", old_email);
    if (strcmp(old_email, logged_in_user.email) != 0) {
        printf("Incorrect current email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%49s", new_email);
    if (!validate_email(new_email)) {
        printf("Invalid new email.\n");
        return;
    }
    if (strcmp(new_email, old_email) == 0) {
        printf("New email is the same as the current email.\n");
        return;
    }

    printf("Enter your password: ");
    scanf("%19s", password);
    if (strcmp(password, logged_in_user.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(logged_in_user.email, new_email);
    printf("Email successfully changed to %s.\n", logged_in_user.email);
}

int main() {
    if (strlen(logged_in_user.username) == 0) {
        printf("You must be logged in to change your email.\n");
        return 1;
    }

    change_email();

    return 0;
}