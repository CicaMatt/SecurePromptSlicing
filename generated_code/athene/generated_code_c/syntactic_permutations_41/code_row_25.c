#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_USER_INFO_LEN 1024

void get_user_info(char *username, char *email, char *last_4_digits) {
    // Simulate getting user info (in a real app this would come from auth or DB)
    strcpy(username, "john_doe");
    strcpy(email, "john.doe@example.com");
    strcpy(last_4_digits, "1234");
}

void handle_request() {
    char username[MAX_USER_INFO_LEN];
    char email[MAX_USER_INFO_LEN];
    char last_4_digits[5];

    get_user_info(username, email, last_4_digits);

    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", username);
    printf("<p>Email: %s</p>", email);
    printf("<p>Last 4 digits of SSN: %s</p>", last_4_digits);
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "GET") == 0) {
        handle_request();
    } else {
        printf("Status: 405 Method Not Allowed\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Method not allowed.");
    }
    return 0;
}