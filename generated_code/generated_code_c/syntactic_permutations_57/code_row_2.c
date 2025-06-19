#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to hold login information
typedef struct {
    char* username;
    char* password;
} LoginInfo;

// Define a struct to hold user information
typedef struct {
    char* email;
    char* password;
} UserInfo;

// Function prototypes
void printLoginInfo(LoginInfo *login_info);
void printUserInfo(UserInfo *user_info);
int isValidEmail(char *email);
int changeEmail(UserInfo *user_info, LoginInfo *login_info);

// Main function
int main() {
    // Create login info struct
    LoginInfo *login_info = malloc(sizeof(LoginInfo));
    login_info->username = "johndoe";
    login_info->password = "password123";

    // Create user info struct
    UserInfo *user_info = malloc(sizeof(UserInfo));
    user_info->email = "johndoe@example.com";
    user_info->password = "password123";

    // Print login info
    printf("Login Info:\n");
    printLoginInfo(login_info);

    // Print user info
    printf("\nUser Info:\n");
    printUserInfo(user_info);

    // Change email
    int result = changeEmail(user_info, login_info);
    if (result == 0) {
        printf("\nEmail changed successfully!\n\n");
    } else {
        printf("\nError changing email!\n\n");
    }

    // Free memory
    free(login_info);
    free(user_info);

    return 0;
}

// Function to print login info
void printLoginInfo(LoginInfo *login_info) {
    printf("Username: %s\n", login_info->username);
    printf("Password: %s\n", login_info->password);
}

// Function to print user info
void printUserInfo(UserInfo *user_info) {
    printf("Email: %s\n", user_info->email);
    printf("Password: %s\n", user_info->password);
}

// Function to check if email is valid
int isValidEmail(char *email) {
    // Check for "@" and ".com" in the email
    if (strchr(email, '@') != NULL && strstr(email, ".com") != NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Function to change email
int changeEmail(UserInfo *user_info, LoginInfo *login_info) {
    // Create new email struct
    char *new_email = malloc(sizeof(char) * 50);

    // Get new email from user
    printf("\nEnter new email: ");
    fgets(new_email, 50, stdin);
    new_email[strcspn(new_email, "\n")] = '\0';

    // Check if new email is valid
    if (isValidEmail(new_email) == 1) {
        // Check if user is logged in
        if (strcmp(login_info->username, user_info->email) == 0 && strcmp(login_info->password, user_info->password) == 0) {
            // Update email
            free(user_info->email);
            user_info->email = new_email;
            
            return 0;
        } else {
            printf("\nError: User is not logged in!\n\n");
            return 1;
        }
    } else {
        printf("\nError: Invalid email address!\n\n");
        return 1;
    }
}