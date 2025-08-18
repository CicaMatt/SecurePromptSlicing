#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LEN];
    int logged_in;
} User;

void login(User *user, const char *email) {
    strcpy(user->email, email);
    user->logged_in = 1;
}

int change_email(User *user, const char *old_email, const char *password, const char *new_email) {
    if (!user->logged_in) return 0;
    if (strcmp(old_email, user->email) != 0 || strcmp(password, PASSWORD) != 0) return 0;
    strcpy(user->email, new_email);
    return 1;
}

int main() {
    User user = {"", 0};
    char old_email[MAX_EMAIL_LEN], password[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN];
    
    // Simulate login
    login(&user, "user@example.com");
    
    printf("Enter your old email: ");
    scanf("%49s", old_email);
    printf("Enter your password: ");
    scanf("%49s", password);
    printf("Enter your new email: ");
    scanf("%49s", new_email);

    if (change_email(&user, old_email, password, new_email)) {
        printf("Email updated successfully to %s\n", user.email);
    } else {
        printf("Failed to update email. Please check your details and try again.\n");
    }

    return 0;
}