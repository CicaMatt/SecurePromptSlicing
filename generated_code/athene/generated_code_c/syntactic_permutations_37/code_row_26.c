#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

int main() {
    char username[100];
    char password[100];

    printf("Content-Type: text/html\n\n");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        FILE *post_data = fopen("/dev/stdin", "r");
        if (post_data == NULL) {
            redirect("/internal_server_error");
            return 1;
        }

        fscanf(post_data, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            redirect("/success");
        } else {
            redirect("/");
        }
    } else {
        printf("<form method='post'>");
        printf("Username: <input type='text' name='username'><br>");
        printf("Password: <input type='password' name='password'><br>");
        printf("<input type='submit'>");
        printf("</form>");
    }

    return 0;
}