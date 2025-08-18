#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* check_mod(const char* query) {
    const char* username = strstr(query, "username=");
    const char* password = strstr(query, "password=");

    if (username && password) {
        username += strlen("username=");
        password += strlen("password=");

        const char* end_username = strchr(username, '&');
        const char* end_password = strchr(password, '&');

        if (end_username) {
            size_t len = end_username - username;
            char user[len + 1];
            strncpy(user, username, len);
            user[len] = '\0';
            username = user;
        }

        if (end_password) {
            size_t len = end_password - password;
            char pass[len + 1];
            strncpy(pass, password, len);
            pass[len] = '\0';
            password = pass;
        }

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            return "true";
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    const char* query = "username=admin&password=password";
    const char* result = check_mod(query);
    if (result) {
        printf("%s\n", result);
    } else {
        printf("false\n");
    }
    return 0;
}