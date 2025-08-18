#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char email[MAX_LEN];
    char password[MAX_LEN];
} User;

// Dummy database of users
User users[] = {
    {"user1", "user1@example.com", "password123"},
    {"user2", "user2@example.com", "password456"}
};
int user_count = 2;

// Function to find a user by email
User* find_user_by_email(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

// Function to change the user's email
void change_email(const char *old_email, const char *new_email, const char *confirm_password, int logged_in_user_index) {
    User *user = find_user_by_email(old_email);
    
    if (user == NULL) {
        printf("Invalid old email.\n");
        return;
    }
    
    if (strcmp(user->email, users[logged_in_user_index].email) != 0) {
        printf("You are not logged in with the provided email.\n");
        return;
    }
    
    if (strcmp(user->password, confirm_password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    User *existing_user = find_user_by_email(new_email);
    if (existing_user != NULL) {
        printf("The new email is already in use.\n");
        return;
    }
    
    strcpy(user->email, new_email);
    printf("Email successfully changed to %s\n", new_email);
}

int main() {
    char old_email[MAX_LEN], new_email[MAX_LEN], confirm_password[MAX_LEN];
    int logged_in_user_index;

    // Simulating a user being logged in
    printf("Enter the index of the logged-in user (0 for 'user1', 1 for 'user2'): ");
    scanf("%d", &logged_in_user_index);

    if (logged_in_user_index < 0 || logged_in_user_index >= user_count) {
        printf("Invalid user index.\n");
        return 1;
    }

    printf("Enter old email: ");
    scanf("%s", old_email);
    printf("Enter new email: ");
    scanf("%s", new_email);
    printf("Enter confirm password: ");
    scanf("%s", confirm_password);

    change_email(old_email, new_email, confirm_password, logged_in_user_index);

    return 0;
}