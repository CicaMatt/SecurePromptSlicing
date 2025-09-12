#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void handle_request(const char *url) {
    if (strncmp(url, "/check_mod?username=", 20) == 0) {
        const char *credentials = url + 20;
        char *username_start = strstr(credentials, "&password=");
        if (!username_start) return;

        *username_start = '\0'; // Null-terminate username
        username_start += 10;   // Move past '&password=' to get password

        char *username = credentials;
        char *password = username_start;

        printf("%s\n", check_mod(username, password));
    }
}

const char* check_mod(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    // Simulated URL input
    const char *url = "/check_mod?username=user&password=pass";
    
    handle_request(url);

    return 0;
}