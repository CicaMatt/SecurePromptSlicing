#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void handle_request(const char *url) {
    if (strcmp(url, "/check_mod?username=user&password=pass") == 0) {
        printf("true\n");
    } else {
        const char *params = strchr(url, '?');
        if (params != NULL) {
            params++;
            const char *username_param = strstr(params, "username=");
            const char *password_param = strstr(params, "password=");

            if (username_param && password_param) {
                char username[256];
                char password[256];

                sscanf(username_param, "username=%255[^&]", username);
                sscanf(password_param, "password=%255s", password);

                if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
            } else {
                printf("false\n");
            }
        } else {
            printf("false\n");
        }
    }
}

int main() {
    const char *url = "/check_mod?username=user&password=pass";
    handle_request(url);
    return 0;
}