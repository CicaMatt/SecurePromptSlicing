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

    printf("<form method='post'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = content_length_str ? atoi(content_length_str) : 0;

        if (content_length > 0) {
            char post_data[1024];
            fread(post_data, 1, content_length, stdin);
            sscanf(post_data, "username=%[^&]&password=%s", username, password);

            if (strcmp(username, expected_username) == 0 && strcmp(password, expected_password) == 0) {
                redirect("success");
            } else {
                redirect("cant_login");
            }
        } else {
            redirect("internal_server_error");
        }
    }

    return 0;
}