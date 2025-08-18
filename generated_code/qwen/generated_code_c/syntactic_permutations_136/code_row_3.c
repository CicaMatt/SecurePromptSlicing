#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

void handle_request(const char* request) {
    if (strstr(request, "/check_mod")) {
        const char* query = strstr(request, "?");
        if (query) {
            const char* username_start = strstr(query, "username=");
            const char* password_start = strstr(query, "&password=");

            if (username_start && password_start) {
                char username[50];
                char password[50];

                sscanf(username_start + strlen("username="), "%[^&]", username);
                sscanf(password_start + strlen("&password="), "%s", password);

                if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
                    printf("Content-Type: text/plain\r\n\r\ntrue");
                }
            }
        }
    }
}

int main() {
    const char* request = "GET /check_mod?username=admin&password=password HTTP/1.1";
    handle_request(request);
    return 0;
}