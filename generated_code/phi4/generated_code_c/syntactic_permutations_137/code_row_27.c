#include <stdio.h>
#include <string.h>

// Simulated structure for HTTP request to demonstrate URL parsing.
typedef struct {
    char url[256];
} HttpRequest;

// Function prototypes
int auth_mod(const char *username, const char *password);
void check_mod(HttpRequest req);

int main() {
    HttpRequest request;
    strcpy(request.url, "/check_mod?username=admin&password=1234");

    check_mod(request);
    return 0;
}

void check_mod(HttpRequest req) {
    // Simulating URL parsing to extract username and password
    char username[50], password[50];
    
    sscanf(req.url + strlen("/check_mod?"), "username=%[^&]&password=%s", username, password);

    if (auth_mod(username, password)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int auth_mod(const char *username, const char *password) {
    // For demonstration purposes: only one set of username and password is considered valid.
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        return 1; // True
    }
    return 0; // False
}