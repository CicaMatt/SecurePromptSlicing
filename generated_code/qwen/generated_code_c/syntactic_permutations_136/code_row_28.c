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
            size_t len = end_username - username;
            char user[len + 1];
            strncpy(user, username, len);
            user[len] = '\0';
            
            password = strchr(password, '=') + 1; // Move pointer past "="
            const char* end_password = strchr(password, '&');
            size_t pass_len = end_password ? end_password - password : strlen(password);
            char pass[pass_len + 1];
            strncpy(pass, password, pass_len);
            pass[pass_len] = '\0';

            if (strcmp(user, USERNAME) == 0 && strcmp(pass, PASSWORD) == 0) {
                return strdup("true");
            }
        }
    }

    return strdup("false");
}

int main() {
    const char* query = "username=admin&password=password";
    char* result = check_mod(query);
    printf("%s\n", result);
    free(result);
    return 0;
}