#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User form = {"admin", "12345"};
User credentials = {"admin", "12345"};

int check_mod() {
    if (strcmp(form.username, credentials.username) == 0 && strcmp(form.password, credentials.password) == 0) {
        return 1;
    }
    return 0;
}

int main() {
    int result = check_mod();
    printf("%s\n", result ? "true" : "false");
    return 0;
}