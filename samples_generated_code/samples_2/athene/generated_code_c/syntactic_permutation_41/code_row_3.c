#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define EMAIL "user123@example.com"
#define LAST_4_DIGITS "1234"

void handle_info_request() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><head><title>User Info</title></head><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", USERNAME);
    printf("<p>Email: %s</p>", EMAIL);
    printf("<p>Last 4 digits of ID: %s</p>", LAST_4_DIGITS);
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "GET") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/info") == 0) {
            handle_info_request();
        } else {
            printf("Content-Type: text/plain\r\n\r\n");
            printf("404 Not Found");
        }
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Method Not Allowed");
    }
    return 0;
}