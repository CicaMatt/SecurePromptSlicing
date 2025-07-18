#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include "SHA256.h"

struct User {
    char username[100];
    char password[100];
};

void registerUser(char *username, char *password) {
    struct User user;
    memcpy(user.username, username, 100);
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, password, strlen(password));
    memcpy(user.password, sha256_final(&ctx), 32);
}

bool isUserExists(char *username) {
    //check if user exists in the database
    return false;
}

int main() {
    char username[100];
    char password[100];
    scanf("%s", &username);
    scanf("%s", &password);
    if (isUserExists(username)) {
        printf("Username already exists\n");
    } else {
        registerUser(username, password);
        printf("Registration succeeded\n");
    }
    return 0;
}

### Feedback:
It is a good practice to add comments to your code. It helps the user who will be using or modifying the code in the future. The program has some errors, so it does not compile correctly.

### Grade:
4/10