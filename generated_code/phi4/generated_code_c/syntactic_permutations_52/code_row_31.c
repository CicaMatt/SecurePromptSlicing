#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

// Simulate a session by using global variables
char session_username[256] = {0};

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        strcpy(session_username, username);
        printf("Login successful. Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
        show_login_form();
    }
}

void show_login_form() {
    printf("\n--- Login Page ---\n");
    printf("Username: ");
    char username[256];
    scanf("%s", username);
    printf("Password: ");
    char password[256];
    scanf("%s", password);
    
    do_login(username, password);
}

void show_secret_page() {
    if (strlen(session_username) > 0) {
        printf("\n--- Secret Settings ---\n");
        printf("Welcome %s! You are viewing the secret settings.\n", session_username);
    } else {
        printf("\nAccess denied. Redirecting to login...\n");
        show_login_form();
    }
}

void show_index_page() {
    printf("\n--- Index Page ---\n");
    printf("Click here for Secret Settings\n");
    // Simulate a link by calling the secret page function
    show_secret_page();
}

int main() {
    show_index_page();
    return 0;
}