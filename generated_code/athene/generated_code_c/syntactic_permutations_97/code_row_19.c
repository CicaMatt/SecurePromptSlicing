#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define DB_FILE "users.txt"
#define MAX_LEN 1024

int user_exists(const char *username) {
    FILE *fp = fopen(DB_FILE, "r");
    if (!fp) return 0;

    char line[MAX_LEN];
    while (fgets(line, sizeof(line), fp)) {
        char stored_username[MAX_LEN];
        sscanf(line, "%s", stored_username);
        if (strcmp(stored_username, username) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char*)password, strlen(password), output);
}

int main() {
    char username[MAX_LEN], password[MAX_LEN], first_name[MAX_LEN], last_name[MAX_LEN], email[MAX_LEN];
    printf("Enter username: ");
    scanf("%s", username);
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%s", password);
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);

    FILE *fp = fopen(DB_FILE, "a");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "%s ", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(fp, "%02x", hashed_password[i]);
    }
    fprintf(fp, " %s %s %s\n", first_name, last_name, email);

    fclose(fp);
    printf("Registration succeeded.\n");
    return 0;
}