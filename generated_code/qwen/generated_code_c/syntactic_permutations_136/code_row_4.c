#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

int check_credentials(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0;
}

char* check_mod(const char *query_string) {
    char username[MAX_USERNAME_LEN] = {0};
    char password[MAX_PASSWORD_LEN] = {0};

    if (sscanf(query_string, "username=%[^&]&password=%s", username, password) != 2) {
        return "false";
    }

    if (check_credentials(username, password)) {
        return "true";
    } else {
        return "false";
    }
}

int main(int argc, char *argv[]) {
    const char *query_string = "username=admin&password=secret";
    printf("%s\n", check_mod(query_string));
    return 0;
}