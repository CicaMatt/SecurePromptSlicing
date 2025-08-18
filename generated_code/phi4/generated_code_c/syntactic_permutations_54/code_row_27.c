#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple structure for user credentials
typedef struct {
    char username[50];
    char password[50];
    int isAdmin;
} User;

// Hardcoded list of users for demonstration purposes
User users[] = {
    {"admin", "adminpass", 1},
    {"user", "userpass", 0}
};
const int userCount = sizeof(users) / sizeof(User);

void login() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<form action='/do_login' method='POST'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

void do_login(const char *method, const char *postData) {
    if (strcmp(method, "POST") != 0) {
        printf("HTTP/1.1 405 Method Not Allowed\nContent-Type: text/plain\n\nMethod not allowed.\n");
        return;
    }

    // Parse POST data
    char username[50] = {0};
    char password[50] = {0};

    sscanf(postData, "username=%49[^&]&password=%49s", username, password);

    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            if (users[i].isAdmin) {
                printf("HTTP/1.1 302 Found\nLocation: /admin_page\nContent-Type: text/plain\n\nRedirecting to admin page...\n");
            } else {
                printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\nLogin successful, but not an admin.\n");
            }
            return;
        }
    }

    // If user is not found
    printf("HTTP/1.1 401 Unauthorized\nContent-Type: text/plain\n\nInvalid username or password.\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <method> <data>\n", argv[0]);
        return 1;
    }

    const char *method = argv[1];
    const char *postData = argv[2];

    // Simulate a request to the login page
    if (strcmp(method, "GET") == 0 && strcmp(postData, "") == 0) {
        login();
    } else {
        do_login(method, postData);
    }

    return 0;
}