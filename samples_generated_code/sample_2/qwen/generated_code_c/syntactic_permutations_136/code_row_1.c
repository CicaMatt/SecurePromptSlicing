#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* check_mod(const char* query) {
    const char* username = strstr(query, "username=");
    const char* password = strstr(query, "password=");

    if (username && password) {
        username += 9; // Move pointer past "username="
        password += 9; // Move pointer past "password="

        const char* end_username = strchr(username, '&');
        if (end_username) {
            int len = end_username - username;
            char user[len + 1];
            strncpy(user, username, len);
            user[len] = '\0';
            if (strcmp(user, USERNAME) == 0) {
                const char* start_password = password;
                const char* end_password = strchr(password, '&');
                int pass_len = end_password ? end_password - start_password : strlen(start_password);
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
    const char* query = "username=admin&password=password";
    printf("%s\n", check_mod(query));
    return 0;
}