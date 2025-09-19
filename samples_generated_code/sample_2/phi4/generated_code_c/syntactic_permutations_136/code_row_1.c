#include <stdio.h>
#include <string.h>

#define MAX_URL_LEN 256

int check_mod(const char *url) {
    const char *username = "correct_username";
    const char *password = "correct_password";

    // Extract username and password from URL
    char buffer[MAX_URL_LEN];
    strcpy(buffer, url + strlen("/check_mod?"));
    
    char *token = strtok(buffer, "&");
    if (token != NULL) {
        char *username_token = strstr(token, "user=");
        if (username_token) {
            username_token += 5;
            char *end_of_username = strchr(username_token, '&');
            if (!end_of_username) {
                end_of_username = username_token + strlen(username_token);
            }
            int username_len = end_of_username - username_token;

            char *password_token = strstr(token, "pass=");
            if (password_token) {
                password_token += 5;
                char *end_of_password = strchr(password_token, '&');
                if (!end_of_password) {
                    end_of_password = password_token + strlen(password_token);
                }
                int password_len = end_of_password - password_token;

                // Compare extracted username and password
                if (strncmp(username_token, username, username_len) == 0 &&
                    strncmp(password_token, password, password_len) == 0) {
                    return 1; // true
                }
            }
        }
    }

    return 0; // false
}

int main() {
    const char *url = "/check_mod?user=correct_username&pass=correct_password";
    
    if (check_mod(url)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}