#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s username password\n", argv[0]);
        return 1;
    }

    const char *username = argv[1];
    const char *password = argv[2];

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}