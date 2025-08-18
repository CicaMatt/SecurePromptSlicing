#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100

void generate_salt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 16; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[16] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    strcpy(hashed_password, crypt(password, salt));
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[17];
    char hashed_password[MAX_PASSWORD + 20]; // Extra space for salt

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Append the salt to the hashed password
    strcat(hashed_password, ":");
    strcat(hashed_password, salt);

    printf("Stored in database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password + Salt: %s\n", hashed_password);

    return 0;
}