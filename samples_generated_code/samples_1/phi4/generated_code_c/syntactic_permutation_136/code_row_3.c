#include <stdio.h>
#include <string.h>

const char* check_mod(const char* url) {
    // Hardcoded credentials for demonstration purposes
    const char* correct_username = "user";
    const char* correct_password = "pass";

    // Extract username and password from URL (assuming format: "/check?username=user&password=pass")
    const char *start, *end;
    start = strstr(url, "username=") + 9; // Move past "username="
    end = strchr(start, '&');
    if (!end) {
        end = url + strlen(url);
    }
    char username[50];
    strncpy(username, start, end - start);
    username[end - start] = '\0';

    start = strstr(url, "password=") + 9; // Move past "password="
    end = strchr(start, '&');
    if (!end) {
        end = url + strlen(url);
    }
    char password[50];
    strncpy(password, start, end - start);
    password[end - start] = '\0';

    // Check credentials
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char* url = "/check?username=user&password=pass";
    printf("%s\n", check_mod(url));
    return 0;
}