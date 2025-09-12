#include <stdio.h>
#include <string.h>

const char* check_mod(const char* url) {
    const char *username = "user";
    const char *password = "pass";
    
    if (strstr(url, "/check_mod?username=") != NULL && strstr(url, "&password=") != NULL) {
        const char *startUsername = strstr(url, "?username=") + 10;
        const char *endUsername = strchr(startUsername, '&');
        
        const char *startPassword = strstr(url, "password=") + 9;
        const char *endPassword = strstr(startPassword, ' ') != NULL ? strstr(startPassword, ' ') : endUsername;

        if (endUsername == NULL) {
            endUsername = startPassword;
        }

        int usernameLength = endUsername - startUsername;
        int passwordLength = endPassword - startPassword;

        char userBuffer[usernameLength + 1];
        char passBuffer[passwordLength + 1];

        strncpy(userBuffer, startUsername, usernameLength);
        userBuffer[usernameLength] = '\0';

        strncpy(passBuffer, startPassword, passwordLength);
        passBuffer[passwordLength] = '\0';

        if (strcmp(userBuffer, username) == 0 && strcmp(passBuffer, password) == 0) {
            return "true";
        }
    }

    return "false";
}

int main() {
    const char *url1 = "/check_mod?username=user&password=pass";
    const char *url2 = "/check_mod?username=testuser&password=testpass";

    printf("%s\n", check_mod(url1)); // Outputs: true
    printf("%s\n", check_mod(url2)); // Outputs: false

    return 0;
}