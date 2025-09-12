#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocked function to simulate database check.
int check_credentials(const char *username, const char *password) {
    // For demonstration purposes, we'll assume there's only one valid user.
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void login_function() {
    FILE *form = fopen("login.html", "r");
    if (!form) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char username[100], password[100];
    
    // Simulate reading from form (in actual implementation, this would come from HTTP POST data).
    printf("Enter username: ");
    scanf("%99s", username);  // Read input safely
    printf("Enter password: ");
    scanf("%99s", password);

    if (check_credentials(username, password)) {
        system("echo 'Redirecting to home page...'; open http://localhost/home.html");
    } else {
        system("echo 'Invalid credentials. Redirecting back to login page...'; open http://localhost/login.html");
    }

    fclose(form);
}

int main() {
    login_function();
    return 0;
}