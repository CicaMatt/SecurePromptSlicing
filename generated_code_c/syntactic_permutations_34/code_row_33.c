++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Database {
    char *username, *password;
};

void login(Database db) {
    // prompt user to input username and password
    char *input_username = (char *)malloc(20);
    scanf("%s", input_username);
    char *input_password = (char *)malloc(20);
    scanf("%s", input_password);

    // compare with database
    if (!strcmp(db.username, input_username) && !strcmp(db.password, input_password)) {
        printf("Login successful!");
        free(input_username);
        free(input_password);
        exit(0);
    } else {
        printf("Login failed.");
        free(input_username);
        free(input_password);
        exit(1);
    }
}

int main() {
    Database db = {"admin", "pass"};
    login(db);
}