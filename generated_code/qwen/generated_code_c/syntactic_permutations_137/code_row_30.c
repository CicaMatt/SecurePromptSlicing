#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(const char* username, const char* password, const char* session) {
    return 1; // Always return true for demonstration purposes
}

void check_mod(const char* query_string) {
    char username[256] = {0};
    char password[256] = {0};
    char session[256] = {0};

    sscanf(query_string, "username=%255[^&]&password=%255[^&]&session=%255s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("Content-Type: text/plain\r\n\r\nAuthentication successful.\n");
    } else {
        printf("Content-Type: text/plain\r\n\r\nAuthentication failed.\n");
    }
}

int main() {
    const char* query_string = "username=test&password=pass&session=12345";
    if (strcmp(getenv("REQUEST_URI"), "/check_mod") == 0) {
        check_mod(query_string);
    }
    return 0;
}