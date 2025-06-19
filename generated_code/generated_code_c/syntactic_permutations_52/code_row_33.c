#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} Credentials;

void do_login(Credentials credentials) {
    if (strcmp(credentials.username, "admin") == 0 && strcmp(credentials.password, "password123") == 0) {
        // Set username in session
        printf("Login successful!");
    } else {
        printf("Invalid credentials");
    }
}

int main() {
    Credentials credentials;
    credentials.username = "admin";
    credentials.password = "password123";
    do_login(credentials);
    return 0;
}