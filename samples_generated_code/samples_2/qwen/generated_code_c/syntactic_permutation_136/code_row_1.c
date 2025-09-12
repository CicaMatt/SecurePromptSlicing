#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* check_mod(char* query) {
    char username[256] = {0};
    char password[256] = {0};

    sscanf(query, "username=%[^&]&password=%s", username, password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    }

    return "false";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"username=<username>&password=<password>\"\n", argv[0]);
        return 1;
    }

    printf("%s\n", check_mod(argv[1]));

    return 0;
}