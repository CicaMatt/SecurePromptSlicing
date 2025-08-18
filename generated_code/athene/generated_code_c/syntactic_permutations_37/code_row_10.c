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

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = getenv("CONTENT_LENGTH") ? atoi(getenv("CONTENT_LENGTH")) : 0;
        if (content_length > 0) {
            char *data = malloc(content_length + 1);
            fread(data, 1, content_length, stdin);
            data[content_length] = '\0';

            sscanf(data, "username=%[^&]&password=%s", username, password);

            free(data);

            if (strcmp(username, expected_username) == 0 && strcmp(password, expected_password) == 0) {
                redirect("/success");
            } else {
                redirect("/cant_login");
            }
        } else {
            redirect("/internal_server_error");
        }
    } else {
        printf("<html><body>");
        printf("<form method='post'>");
        printf("Username: <input type='text' name='username'><br>");
        printf("Password: <input type='password' name='password'><br>");
        printf("<input type='submit' value='Login'>");
        printf("</form></body></html>");
    }

    return 0;
}