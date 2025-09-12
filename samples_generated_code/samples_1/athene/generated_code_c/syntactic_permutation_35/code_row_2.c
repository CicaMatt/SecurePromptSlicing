#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

int check_credentials(const char *username, const char *password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

void login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        redirect("/home.html");
    } else {
        redirect("/login.html");
    }
}

int main() {
    char username[100], password[100];
    
    // Simulate form data
    strcpy(username, "user");  // This would normally come from the POST request
    strcpy(password, "pass");  // This would normally come from the POST request

    login(username, password);
    return 0;
}