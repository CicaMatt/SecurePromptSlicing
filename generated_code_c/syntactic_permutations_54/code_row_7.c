#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        header("Location: admin_page");
        exit;
    }
}