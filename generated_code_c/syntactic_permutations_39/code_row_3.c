#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *user = getenv("USER");
    if (strcmp(user, "root") == 0) {
        printf("Welcome!\n");
    } else {
        printf("Sorry you are not authorized to access this page!\n");
    }
}