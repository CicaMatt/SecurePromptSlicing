#include <stdio.h>
#include <string.h>

// Simple mock functions for handling sessions and redirections.
void set_session_username(const char *username) {
    // In a real application, this would store the username in session storage.
    printf("Session username set to: %s\n", username);
}

void redirect_to_page(const char *page_name) {
    if (strcmp(page_name, "secret") == 0) {
        secret_page();
    } else {
        index_page();
    }
}

// Function prototypes
void do_login(const char *username, const char *password);
void index_page();
void secret_page();

int main() {
    // Simulate visiting the index page.
    index_page();
    return 0;
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        set_session_username(username);
        redirect_to_page("secret");
    } else {
        printf("Invalid username or password. Please try again.\n");
        index_page();
    }
}

void index_page() {
    printf("Index Page\n");
    printf("Visit: [Login](#login)\n");

    // Simulate login attempt
    char input_username[50], input_password[50];
    
    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    do_login(input_username, input_password);
}

void secret_page() {
    printf("\nSecret Page\n");
    printf("Secret settings\n");
}