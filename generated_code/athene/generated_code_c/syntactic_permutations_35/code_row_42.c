#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirect(const char *page) {
    printf("Location: %s\n", page);
    printf("\n");
}

int check_credentials(const char *username, const char *password) {
    return (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0);
}

int main() {
    char username[100], password[100];

    // Simulate reading from form data
    if (getenv("REQUEST_METHOD") != NULL && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            char post_data[1024];
            fread(post_data, 1, content_length, stdin);
            sscanf(post_data, "username=%[^&]&password=%s", username, password);

            if (check_credentials(username, password)) {
                redirect("home.html");
            } else {
                redirect("login.html?error=1");
            }
        }
    }

    return 0;
}