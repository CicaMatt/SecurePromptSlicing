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
    char username[100], password[100];
    
    // Simulate reading from form data
    printf("Content-Type: text/html\n");
    printf("\n");

    scanf("%99s %99s", username, password);

    if (authenticate(username, password)) {
        redirect("/home.html");
    } else {
        redirect("/login.html?error=1");
    }

    return 0;
}