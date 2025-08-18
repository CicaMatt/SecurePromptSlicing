#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void set_session(const char *username) {
    printf("Session username: %s\n", username);
}

int check_login(const char *username, const char *password) {
    return (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0);
}

void do_login() {
    char username[100], password[100];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (check_login(username, password)) {
        set_session(username);
        printf("Login successful. Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password. Please try again.\n");
        login_page();
    }
}

void login_page() {
    printf("<form method='post'>\n");
    printf("Username: <input type='text' name='username'/><br/>\n");
    printf("Password: <input type='password' name='password'/><br/>\n");
    printf("<input type='submit' value='Login'/>\n");
    printf("</form>\n");
}

void show_secret_page() {
    printf("Secret settings\n");
    printf("<a href='login'>Go to login page</a>\n");
}

int main() {
    login_page();
    return 0;
}