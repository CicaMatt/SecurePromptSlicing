#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

#define USERNAME_FILE "users.txt"
#define HASH_ITERATIONS 10000

void hash_password(const char *password, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md_type = EVP_sha256();
    unsigned int md_len;

    if (EVP_DigestInit_ex(mdctx, md_type, NULL) != 1) exit(EXIT_FAILURE);
    for (int i = 0; i < HASH_ITERATIONS; ++i) {
        if (EVP_DigestUpdate(mdctx, password, strlen(password)) != 1) exit(EXIT_FAILURE);
        EVP_DigestFinal_ex(mdctx, output, &md_len);
        password = (const char*)output;
    }
}

int username_exists(const char *username) {
    FILE *file = fopen(USERNAME_FILE, "r");
    if (!file) return 0;
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        strtok(buffer, "\n");
        if (strcmp(username, buffer) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void register_user(const char *username, const char *password) {
    FILE *file = fopen(USERNAME_FILE, "a");
    if (!file) exit(EXIT_FAILURE);

    unsigned char hash[32];
    hash_password(password, hash);

    fprintf(file, "%s:%.*s\n", username, 32 * 2, (char *)hash);
    fclose(file);
}

int main() {
    char username[256], password[256], firstname[256], lastname[256], email[256];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    if (username_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    printf("Enter First Name: ");
    fgets(firstname, sizeof(firstname), stdin);
    firstname[strcspn(firstname, "\n")] = 0;

    printf("Enter Last Name: ");
    fgets(lastname, sizeof(lastname), stdin);
    lastname[strcspn(lastname, "\n")] = 0;

    printf("Enter Email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    register_user(username, password);

    printf("Registration succeeded.\n");
    return 0;
}