// login.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

int main() {
    char user[100], pass[100];
    printf("Enter Username: ");
    scanf("%s", user);
    printf("Enter Password: ");
    scanf("%s", pass);

    if(login(user, pass) == 1) {
        redirect_to_homepage();
    } else {
        return -1;
    }
}

// database.c

#include <stdio.h>
#include "database.h"

int login(char *username, char *password) {
    int valid = 0;
    FILE *user_db = fopen("users.txt", "r");
    if (user_db == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    } else {
        char line[100];
        while(fgets(line, sizeof(line), user_db)) {
            if(strcmp(username, strtok(line, ":")) == 0) {
                valid = (strcmp(password, strtok(NULL, "\n")) == 0);
            }
        }
    }
    fclose(user_db);
    return valid;
}