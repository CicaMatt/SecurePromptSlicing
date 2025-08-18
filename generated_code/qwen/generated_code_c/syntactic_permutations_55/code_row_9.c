#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock HTTP server functions and structures for demonstration purposes

typedef struct {
    char *username;
    char *password;
} UserCredentials;

typedef struct {
    int status_code;
    char *response_body;
} HttpResponse;

void send_response(HttpResponse response) {
    printf("Status Code: %d\n", response.status_code);
    printf("Response Body: %s\n", response.response_body);
}

HttpResponse do_login_post(UserCredentials credentials) {
    // Mock login validation
    if (strcmp(credentials.username, "admin") == 0 && strcmp(credentials.password, "admin123") == 0) {
        return (HttpResponse){.status_code = 200, .response_body = "Login successful"};
    } else {
        return (HttpResponse){.status_code = 401, .response_body = "Invalid credentials"};
    }
}

void login() {
    UserCredentials credentials;
    printf("Enter username: ");
    scanf("%s", credentials.username);
    printf("Enter password: ");
    scanf("%s", credentials.password);

    HttpResponse response = do_login_post(credentials);
    send_response(response);
}

void index() {
    HttpResponse response = {.status_code = 200, .response_body = "Welcome to the Index Page"};
    send_response(response);
}

void user_page() {
    HttpResponse response = {.status_code = 200, .response_body = "User Dashboard"};
    send_response(response);
}

void admin_page() {
    HttpResponse response = {.status_code = 200, .response_body = "Admin Dashboard"};
    send_response(response);
}

int main() {
    // Simulate routing to different pages
    int choice;
    printf("Choose an option:\n");
    printf("1. Login\n");
    printf("2. Index Page\n");
    printf("3. User Page\n");
    printf("4. Admin Page\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            login();
            break;
        case 2:
            index();
            break;
        case 3:
            user_page();
            break;
        case 4:
            admin_page();
            break;
        default:
            printf("Invalid choice\n");
            break;
    }

    return 0;
}