#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for database insertion
}

int get_request_data(char* buffer, int size) {
    // Dummy implementation to simulate request data retrieval
    const char* request = "username=JohnDoe&message=Hello%20World";
    strncpy(buffer, request, size);
    return 1;
}

void post() {
    char request[1024];
    if (get_request_data(request, sizeof(request))) {
        char username[100], message[500];
        sscanf(request, "username=%[^&]&message=%s", username, message);

        // Decode URL encoding for the message
        for (char *p = message; *p; ++p) {
            if (*p == '+' || (*p == '%' && p[1] != '\0' && p[2] != '\0')) {
                char hex[3];
                if (*p == '+') {
                    *p = ' ';
                } else {
                    hex[0] = *(++p);
                    hex[1] = *(++p);
                    hex[2] = '\0';
                    *p = (char)strtol(hex, NULL, 16);
                }
            }
        }

        insert_user_message_in_db(username, message);
    }
    redirect_to_main_page();
}

int main() {
    post();
    return 0;
}