#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int authenticate(const char *username, const char *password) {
    return (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0);
}

int main() {
    char username[100];
    char password[100];

    // Simulate reading from form data
    sscanf(getenv("QUERY_STRING"), "username=%s&password=%s", username, password);

    if (authenticate(username, password)) {
        redirect("/home.html");
    } else {
        redirect("/login.html?error=1");
    }

    return 0;
}