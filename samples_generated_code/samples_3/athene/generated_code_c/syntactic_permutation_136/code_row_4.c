#include <stdio.h>
#include <string.h>

char* check_credentials(const char* url) {
    const char* username = "user123";
    const char* password = "pass456";
    
    const char* usernameParam = "username=";
    const char* passwordParam = "&password=";
    
    const char* startUsername = strstr(url, usernameParam);
    if (!startUsername) return "false";
    startUsername += strlen(usernameParam);

    const char* startPassword = strstr(startUsername, passwordParam);
    if (!startPassword) return "false";
    *startPassword = '\0';
    startPassword += strlen(passwordParam);
    
    if (strcmp(startUsername, username) == 0 && strcmp(startPassword, password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char* url = "/?username=user123&password=pass456";
    printf("%s\n", check_credentials(url));
    return 0;
}