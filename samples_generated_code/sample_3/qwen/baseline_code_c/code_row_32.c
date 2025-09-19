#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

        size_t username_len = (end_username ? end_username - username : strlen(username));
        size_t password_len = (end_password ? end_password - password : strlen(password));

        if (strncmp(username, USERNAME, username_len) == 0 && strncmp(password, PASSWORD, password_len) == 0) {
            return strdup("true");
        }
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    const char* query = "username=admin&password=password";
    char* result = check_mod(query);

    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("false\n");
    }

    return 0;
}