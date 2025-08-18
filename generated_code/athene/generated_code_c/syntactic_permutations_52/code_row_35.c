#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

Session session;

void set_session_username(const char *username) {
    strncpy(session.username, username, MAX_USERNAME_LEN);
}

int check_login(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "123456";
    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

void do_login() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_login(username, password)) {
        set_session_username(username);
        printf("Login successful. Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void show_index_page() {
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void show_secret_page() {
    if (strlen(session.username) == 0) {
        printf("You are not logged in. Please <a href=\"/login\">log in</a>.\n");
    } else {
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Show Index Page\n2. Login\n3. Show Secret Page\n4. Exit\nChoose an option: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                show_index_page();
                break;
            case 2:
                do_login();
                break;
            case 3:
                show_secret_page();
                break;
            case 4:
                return 0;
        }
    }
}