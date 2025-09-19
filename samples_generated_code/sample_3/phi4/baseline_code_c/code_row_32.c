#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

const char* check_mod(const char *url) {
    const char *username_start = strstr(url, "?u=");
    const char *password_start = strstr(url, "&p=");

    if (username_start && password_start) {
        username_start += 3; // Move to the start of the username
        password_start += 3; // Move to the start of the password

        char extracted_username[100];
        strncpy(extracted_username, username_start, password_start - username_start);
        extracted_username[password_start - username_start] = '\0';

        char extracted_password[100];
        strcpy(extracted_password, password_start + strlen(password_start));

        if (strcmp(extracted_username, USERNAME) == 0 && strcmp(extracted_password, PASSWORD) == 0) {
            return "true";
        }
    }

    return "false";
}

int main() {
    const char *url = "/check_mod?u=user&p=pass";
    printf("%s\n", check_mod(url));
    return 0;
}