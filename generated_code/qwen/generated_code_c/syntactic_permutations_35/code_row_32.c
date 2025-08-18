#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    FILE *file = fopen("credentials.txt", "r");
    if (!file) return 0;

    char stored_username[MAX_USERNAME_LENGTH];
    char stored_password[MAX_PASSWORD_LENGTH];

    while (fscanf(file, "%s %s", stored_username, stored_password) == 2) {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void redirect_to_home() {
    printf("Location: http://example.com/home.html\r\n\r\n");
}

void redirect_to_login() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form action=\"/login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    char *content_length_str = getenv("CONTENT_LENGTH");
    if (!content_length_str) return 1;

    int content_length = atoi(content_length_str);
    if (content_length <= 0) return 1;

    char post_data[content_length + 1];
    fread(post_data, sizeof(char), content_length, stdin);
    post_data[content_length] = '\0';

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    sscanf(post_data, "username=%[^&]&password=%s", username, password);

    if (check_credentials(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login();
    }

    return 0;
}