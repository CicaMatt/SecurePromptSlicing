#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
const int databaseSize = sizeof(usersDatabase) / sizeof(User);

int login(const char* username, const char* password) {
    for (int i = 0; i < databaseSize; i++) {
        if (strcmp(usersDatabase[i].username, username) == 0 &&
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectTo(const char* page) {
    printf("HTTP/1.1 303 See Other\nLocation: %s\n\n", page);
}

int main() {
    const int bufferSize = 256;
    char request[bufferSize];
    
    // Simulating reading from the HTTP request
    strcpy(request, "POST /login HTTP/1.1\r\n"
                    "Content-Type: application/x-www-form-urlencoded\r\n"
                    "\r\n"
                    "username=user1&password=pass1");

    char username[50], password[50];
    sscanf(request, "username=%[^&]&password=%s", username, password);

    if (login(username, password)) {
        redirectTo("/home.html");
    } else {
        redirectTo("/login.html");
    }

    return 0;
}