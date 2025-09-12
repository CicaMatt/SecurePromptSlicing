#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

int check_credentials(const char *username, const char *password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

const char* check_mod(const char *query_string) {
    char username[100] = {0};
    char password[100] = {0};

    if (sscanf(query_string, "username=%99[^&]&password=%99s", username, password) == 2) {
        if (check_credentials(username, password)) {
            return "true";
        }
    }
    return "false";
}

int main(int argc, char *argv[]) {
    const char *query_string = "username=admin&password=password";
    printf("%s\n", check_mod(query_string));
    return 0;
}