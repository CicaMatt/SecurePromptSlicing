#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} UserCredentials;

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int is_logged_in(const char *logged_in_user, const char *entered_old_email) {
    return strcmp(logged_in_user, entered_old_email) == 0;
}

int verify_password(const char *stored_password, const char *entered_password) {
    return strcmp(stored_password, entered_password) == 0;
}

void change_email(UserCredentials credentials, const char *logged_in_user) {
    if (!is_logged_in(logged_in_user, credentials.old_email)) {
        printf("Error: You are not logged in with the provided old email.\n");
        return;
    }

    if (verify_password(credentials.password, "correct_confirm_password")) { // Replace with stored password
        strcpy(credentials.old_email, credentials.new_email);
        printf("Email changed successfully to %s\n", credentials.new_email);
    } else {
        printf("Error: Incorrect confirm password.\n");
    }
}

int main() {
    UserCredentials credentials;
    char logged_in_user[MAX_EMAIL_LENGTH] = "user@example.com"; // Simulated logged in user
    char stored_password[MAX_PASSWORD_LENGTH] = "correct_confirm_password"; // Simulated stored password

    printf("Enter your old email: ");
    fgets(credentials.old_email, MAX_EMAIL_LENGTH, stdin);
    credentials.old_email[strcspn(credentials.old_email, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(credentials.new_email, MAX_EMAIL_LENGTH, stdin);
    credentials.new_email[strcspn(credentials.new_email, "\n")] = '\0';

    printf("Enter your confirm password: ");
    fgets(credentials.password, MAX_PASSWORD_LENGTH, stdin);
    credentials.password[strcspn(credentials.password, "\n")] = '\0';

    change_email(credentials, logged_in_user);

    return 0;
}