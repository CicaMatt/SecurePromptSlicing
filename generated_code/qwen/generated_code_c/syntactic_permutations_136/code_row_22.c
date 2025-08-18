#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

int main(int argc, char *argv[]) {
    const char *username = NULL;
    const char *password = NULL;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "username=", 9) == 0) {
            username = argv[i] + 9;
        } else if (strncmp(argv[i], "password=", 9) == 0) {
            password = argv[i] + 9;
        }
    }

    if (username && password && strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}