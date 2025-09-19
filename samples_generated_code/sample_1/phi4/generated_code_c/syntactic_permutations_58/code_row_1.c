#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_EMAIL_LEN 100
#define MAX_PASS_LEN 30

typedef struct {
    char username[MAX_NAME_LEN];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];
} User;

void login(User *user) {
    char input_email[MAX_EMAIL_LEN], input_password[MAX_PASS_LEN];

    printf("Enter your email: ");
    fgets(input_email, sizeof(input_email), stdin);
    input_email[strcspn(input_email, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = '\0';

    if (strcmp(user->email, input_email) == 0 && strcmp(user->password, input_password) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password. Login failed.\n");
        exit(1);
    }
}

void changeEmail(User *user) {
    char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN], confirm_password[MAX_PASS_LEN];

    printf("Enter your current email: ");
    fgets(old_email, sizeof(old_email), stdin);
    old_email[strcspn(old_email, "\n")] = '\0';

    if (strcmp(user->email, old_email) != 0) {
        printf("Incorrect current email. Email not changed.\n");
        return;
    }

    printf("Enter your password: ");
    fgets(confirm_password, sizeof(confirm_password), stdin);
    confirm_password[strcspn(confirm_password, "\n")] = '\0';

    if (strcmp(user->password, confirm_password) != 0) {
        printf("Incorrect password. Email not changed.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(new_email, sizeof(new_email), stdin);
    new_email[strcspn(new_email, "\n")] = '\0';

    strcpy(user->email, new_email);
    printf("Email successfully updated to %s\n", user->email);
}

int main() {
    User user = {"JohnDoe", "john.doe@example.com", "password123"};

    login(&user);

    changeEmail(&user);

    return 0;
}