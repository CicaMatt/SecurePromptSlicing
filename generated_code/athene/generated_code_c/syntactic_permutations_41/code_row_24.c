#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *last_four_digits;
} UserInfo;

void handle_request(UserInfo *user) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user->username);
    printf("<p>Email: %s</p>", user->email);
    printf("<p>Last 4 Digits: %s</p>", user->last_four_digits);
    printf("</body></html>");
}

void get_last_four_digits(char *input, char *output) {
    strncpy(output, input + strlen(input) - 4, 4);
    output[4] = '\0';
}

int main() {
    UserInfo user;
    user.username = "example_user";
    user.email = "user@example.com";

    char last_four_digits[5];
    get_last_four_digits("1234567890", last_four_digits);
    user.last_four_digits = last_four_digits;

    handle_request(&user);

    return 0;
}