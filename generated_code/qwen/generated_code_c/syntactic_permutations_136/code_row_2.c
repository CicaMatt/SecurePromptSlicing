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
        if (end_username) {
            size_t len = end_username - username;
            char user[len + 1];
            strncpy(user, username, len);
            user[len] = '\0';
            if (strcmp(user, USERNAME) == 0) {
                const char* start_password = password;
                const char* end_password = strchr(password, '&');
                if (!end_password) end_password = password + strlen(password);
                size_t pass_len = end_password - start_password;
                char pass[pass_len + 1];
                strncpy(pass, start_password, pass_len);
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
    if (argc < 2) {
        printf("Usage: %s \"username=xxx&password=yyy\"\n", argv[0]);
        return 1;
    }

    const char* result = check_mod(argv[1]);
    printf("%s\n", result);

    return 0;
}