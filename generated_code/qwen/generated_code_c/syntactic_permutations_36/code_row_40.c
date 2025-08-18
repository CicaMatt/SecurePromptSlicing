#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock database for demonstration purposes
#define MAX_USERS 10
char usernames[MAX_USERS][50] = {"user1", "user2"};
char passwords[MAX_USERS][50] = {"pass1", "pass2"};
int user_count = 2;

bool check_credentials(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(usernames[i], username) == 0) {
            return strcmp(passwords[i], password) == 0;
        }
    }
    return false;
}

void redirect_to_home_page() {
    printf("Redirecting to Home Page...\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        redirect_to_home_page();
    } else {
        printf("Invalid Credentials\n");
    }

    return 0;
}