#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int login(const char* username, const char* password) {
    // Simulated check for valid credentials
    if (strcmp(username, "user") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

int do_login(const char* post_data) {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    sscanf(post_data, "username=%49s&password=%49s", username, password);

    return login(username, password);
}

void index() {
    printf("Welcome to the Index Page\n");
}

void user_page() {
    printf("Welcome to the User Page\n");
}

void admin_page() {
    printf("Welcome to the Admin Page\n");
}

int main() {
    char post_data[] = "username=user&password=password123";
    
    if (do_login(post_data)) {
        index();
        user_page();
        admin_page();
    } else {
        printf("Login Failed. Invalid Credentials.\n");
    }

    return 0;
}