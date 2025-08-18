#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
} Session;

Session session = {0};

void redirect(const char* location) {
    printf("Redirecting to: %s\n", location);
}

int do_login(const char* input_username, const char* input_password) {
    if (strcmp(input_username, "admin") == 0 && strcmp(input_password, "password123") == 0) {
        strcpy(session.username, input_username);
        return 1; // Success
    }
    return 0; // Failure
}

void login_page() {
    char username[50], password[50];
    
    printf("Login Page\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (do_login(username, password)) {
        redirect("/secret");
    } else {
        printf("Invalid credentials.\n");
    }
}

void index_page() {
    printf("Index Page\n");
    printf("<a href='/login'>Login</a>\n");
}

void secret_page() {
    if (session.username[0] != '\0') {
        printf("Secret settings\n");
    } else {
        printf("Access Denied.\n");
    }
}

int main() {
    char command[10];
    
    while (1) {
        printf("\nEnter page (index, login, secret): ");
        scanf("%9s", command);

        if (strcmp(command, "index") == 0) {
            index_page();
        } else if (strcmp(command, "login") == 0) {
            login_page();
        } else if (strcmp(command, "secret") == 0) {
            secret_page();
        } else {
            printf("Unknown command.\n");
        }
    }

    return 0;
}