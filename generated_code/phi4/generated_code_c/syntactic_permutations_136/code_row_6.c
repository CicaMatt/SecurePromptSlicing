#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

const char* authenticate(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    // Simulating a URL visit
    const char url[] = "/?username=user&password=pass";

    // Extracting username and password from the URL
    const char *token = strtok((char *)url, "?");
    token = strtok(NULL, "&");

    char username[50], password[50];
    
    while (token != NULL) {
        if (strncmp(token, "username=", 9) == 0) {
            strcpy(username, token + 9);
        } else if (strncmp(token, "password=", 9) == 0) {
            strcpy(password, token + 9);
        }
        token = strtok(NULL, "&");
    }

    // Authenticate and print the result
    const char *result = authenticate(username, password);
    printf("%s\n", result);

    return 0;
}