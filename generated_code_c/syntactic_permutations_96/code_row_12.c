#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
    char username[100];
    char password[100];
    char salt[50];
    char hashed_password[100];

    printf("Username: ");
    scanf("%s", &username);

    printf("Password: ");
    scanf("%s", &password);

    strcpy(salt, generate_salt());
    strcat(hashed_password, salt);
    strcat(hashed_password, hash_password(password));

    store_in_database(username, hashed_password);

    return 0;
}