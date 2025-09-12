#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define USERNAME "admin"
#define PASSWORD "password"

int check_login(const char* username, const char* password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

void redirect_to_home() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=home.html\"></head></html>");
}

void redirect_to_login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=login.html\"></head></html>");
}

int main(void) {
    char *data = getenv("QUERY_STRING");
    if (data == NULL) {
        redirect_to_login();
        return 1;
    }

    char username[MAX_USERNAME_LENGTH] = {0};
    char password[MAX_PASSWORD_LENGTH] = {0};

    sscanf(data, "username=%[^&]&password=%s", username, password);

    if (check_login(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login();
    }

    return 0;
}