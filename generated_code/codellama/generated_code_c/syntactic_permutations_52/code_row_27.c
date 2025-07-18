#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>

int do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123")) {
        // set username in session
        return 1;
    }
    return 0;
}

void secret_page() {
    printf("Secret settings");
}

int main(int argc, char *argv[]) {
    char *username = "admin";
    char *password = "password123";

    // check login
    if (do_login(username, password)) {
        secret_page();
    } else {
        printf("Invalid credentials");
    }

    return 0;
}