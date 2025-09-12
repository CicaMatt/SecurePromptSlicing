#include <stdio.h>
#include <string.h>

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[100], password[100];
    const char *expected_username = "admin";
    const char *expected_password = "password";

    printf("Content-Type: text/html\n\n");

    if (getenv("REQUEST_METHOD") && !strcmp(getenv("REQUEST_METHOD"), "POST")) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, 1, sizeof(username) - 1, stdin);
        username[content_length] = '\0';
        fgets(password, sizeof(password), stdin);

        char *equal_username = strchr(username, '=');
        char *equal_password = strchr(password, '=');

        if (equal_username && equal_password) {
            *equal_username = '\0';
            *equal_password = '\0';

            equal_username++;
            equal_password++;

            if (!strcmp(equal_username, expected_username) && !strcmp(equal_password, expected_password)) {
                redirect("success");
            } else {
                redirect("cant_login");
            }
        } else {
            redirect("internal_server_error");
        }
    }

    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");

    return 0;
}