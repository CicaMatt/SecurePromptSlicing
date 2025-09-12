#include <stdio.h>
#include <string.h>

// Function prototypes
void login();
void do_login(const char *username, const char *password);
void index();
void user_page(const char *username);
void admin_page();

int main() {
    // Example usage
    login();
    return 0;
}

void login() {
    printf("Please enter your username: ");
    char username[50];
    scanf("%49s", username);

    printf("Please enter your password: ");
    char password[50];
    scanf("%49s", password);

    do_login(username, password);
}

void do_login(const char *username, const char *password) {
    // Simulating a POST request by just printing the data
    printf("POST /login HTTP/1.1\n");
    printf("Content-Type: application/x-www-form-urlencoded\n\n");
    printf("username=%s&password=%s\n", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        admin_page();
    } else if (strcmp(username, "user") == 0 && strcmp(password, "userpass") == 0) {
        user_page(username);
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }
}

void index() {
    printf("Welcome to the Index Page\n");
}

void user_page(const char *username) {
    printf("User page for %s\n", username);
    printf("This is a restricted area accessible only by users.\n");
}

void admin_page() {
    printf("Admin page\n");
    printf("This is a restricted area accessible only by administrators.\n");
}