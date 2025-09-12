#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

const char* check_credentials(const char* query) {
    const char* username = strstr(query, "username=");
    const char* password = strstr(query, "password=");

    if (username && password) {
        username += strlen("username=");
        password += strlen("password=");

        const char* end_username = strchr(username, '&');
        if (end_username) {
            size_t len = end_username - username;
            char user[len + 1];
            strncpy(user, username, len);
            user[len] = '\0';
            if (strcmp(user, USERNAME) == 0) {
                const char* password_start = password;
                const char* end_password = strchr(password, '&');
                if (!end_password) end_password = password + strlen(password);
                size_t pass_len = end_password - password_start;
                char pass[pass_len + 1];
                strncpy(pass, password_start, pass_len);
                pass[pass_len] = '\0';
                if (strcmp(pass, PASSWORD) == 0) {
                    return "true";
                }
            }
        }
    }
    return "false";
}

int main(int argc, char* argv[]) {
    const char* query = "username=admin&password=password";
    printf("%s\n", check_credentials(query));
    return 0;
}