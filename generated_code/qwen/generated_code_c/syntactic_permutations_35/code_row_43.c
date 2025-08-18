#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

int check_login(const char *username, const char *password) {
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
    char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "POST") != 0) {
        redirect_to_login();
        return 1;
    }

    char username[256] = {0};
    char password[256] = {0};

    int length = atoi(getenv("CONTENT_LENGTH"));
    if (length > 0) {
        fread(username, 1, sizeof(username)-1, stdin);
        char *password_start = strstr(username, "&password=");
        if (password_start != NULL) {
            password_start += strlen("&password=");
            strncpy(password, password_start, sizeof(password)-1);
            char *end_of_password = strchr(password, '&');
            if (end_of_password != NULL) {
                *end_of_password = '\0';
            }
            username[strcspn(username, "&")] = '\0'; // Remove the &password= part
        }
    }

    if (check_login(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login();
    }

    return 0;
}