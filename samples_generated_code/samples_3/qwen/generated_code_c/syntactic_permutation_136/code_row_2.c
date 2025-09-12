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
        
        // Find the end of the username
        char* end_of_username = strchr(username, '&');
        if (end_of_username) {
            *end_of_username = '\0';
        }

        // Find the end of the password
        char* end_of_password = strchr(password, '&');
        if (end_of_password) {
            *end_of_password = '\0';
        }

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            return strdup("true");
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