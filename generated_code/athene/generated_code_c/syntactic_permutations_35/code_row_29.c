#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

int check_credentials(const char *username, const char *password) {
    return (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0);
}

int main() {
    char username[100], password[100];
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);

    if (check_credentials(username, password)) {
        redirect("/home.html");
    } else {
        redirect("/login.html?error=1");
    }

    return 0;
}