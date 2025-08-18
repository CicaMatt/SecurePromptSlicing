#include <stdio.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
}

int main() {
    const char *username = "admin";
    const char *password = "123456";

    char input_username[100];
    char input_password[100];

    printf("Content-Type: text/html\n\n");

    printf("<html><body>");
    printf("<form method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form>");
    printf("</body></html>");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        char *data = getenv("QUERY_STRING");
        sscanf(data, "username=%[^&]&password=%s", input_username, input_password);

        if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
            redirect("/success");
        } else {
            redirect("/cant_login");
        }
    }

    return 0;
}