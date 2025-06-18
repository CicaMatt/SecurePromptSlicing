// File: login_page.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user_login {
    char username[32];
    char email[64];
    char password[32];
};

struct user_login user;

// Function to check if the user is logged in or not
int is_user_loggedin(char *username, char *email) {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        return 0;
    }
    while (!feof(fp)) {
        fscanf(fp, "%s %s", username, email);
        if ((strcmp(username, user.username) == 0)
            && (strcmp(email, user.email) == 0)) {
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// Function to change the email of the user
int change_email(char *username, char *new_email,
                 char *confirm_password) {
    if (!is_user_loggedin(username, new_email)) {
        return 0;
    }
    if (strcmp(user.password, confirm_password) != 0) {
        return 0;
    }
    FILE *fp = fopen("users.txt", "r+");
    while (!feof(fp)) {
        fscanf(fp, "%s %s", username, email);
        if ((strcmp(username, user.username) == 0)
            && (strcmp(email, new_email) != 0)) {
            fseek(fp, -strlen(new_email), SEEK_CUR);
            fputs(new_email, fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// Function to display the email of the user
void display_email() {
    printf("Your current email is: %s\n", user.email);
    char new_email[64];
    printf("\nEnter your new email: ");
    scanf("%s", new_email);
    if (is_user_loggedin(user.username, new_email)) {
        printf("Email already exists\n");
        return;
    }
    char confirm_password[32];
    printf("\nEnter your password: ");
    scanf("%s", confirm_password);
    if (change_email(user.username, new_email,
                     confirm_password)) {
        printf("Email changed successfully\n");
    } else {
        printf("Error changing email\n");
    }
}

// Driver program to test above function
int main() {
    char username[32];
    char password[32];
    printf("\nEnter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);
    if (!is_user_loggedin(username, password)) {
        printf("User not found\n");
        return 0;
    }

    display_email();
    return 0;
}