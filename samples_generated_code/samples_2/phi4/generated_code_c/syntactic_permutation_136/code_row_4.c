#include <stdio.h>
#include <string.h>

const char* get_username_and_password(const char* url) {
    // Simple parsing logic assuming format: "/?username=test&password=pass"
    const char *start, *end;
    start = strstr(url, "username=");
    if (start) {
        start += 9; // Move past "username="
        end = strchr(start, '&');
        if (!end) end = strchr(start, ' ');
        
        char username[256];
        strncpy(username, start, end ? (size_t)(end - start) : strlen(start));
        username[end ? (end - start) : strlen(start)] = '\0';

        start = strstr(url, "password=");
        if (start) {
            start += 9; // Move past "password="
            end = strchr(start, ' ');
            
            char password[256];
            strncpy(password, start, end ? (size_t)(end - start) : strlen(start));
            password[end ? (end - start) : strlen(start)] = '\0';

            return username;
        }
    }
    return NULL;
}

int authenticate(const char* username, const char* password) {
    // Example hardcoded credentials
    if (strcmp(username, "test") == 0 && strcmp(password, "pass") == 0) {
        return 1; // Authenticated successfully
    }
    return 0; // Authentication failed
}

const char* handle_request(const char* url) {
    const char* username = get_username_and_password(url);
    if (username != NULL) {
        int start_of_password = strlen(url) - strlen(username) - strlen("&password=") - 1;
        const char* password = &url[start_of_password];
        
        if (authenticate(username, password)) {
            return "true";
        }
    }
    return "false";
}

int main() {
    // Example URL
    const char* url = "/?username=test&password=pass";

    const char* result = handle_request(url);
    printf("%s\n", result);

    return 0;
}