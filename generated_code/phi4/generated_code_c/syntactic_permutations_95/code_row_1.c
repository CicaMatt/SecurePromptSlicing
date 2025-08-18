#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16

typedef struct {
    char username[50];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[EVP_MAX_MD_SIZE];
} UserRecord;

int generate_salt(unsigned char *salt, size_t length) {
    return RAND_bytes(salt, length);
}

int hash_password(const char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    int md_len, i;

    if (EVP_DigestInit_ex(&mdctx, EVP_sha256(), NULL) != 1)
        return -1;

    if (EVP_DigestUpdate(mdctx, password, strlen(password)) != 1)
        return -1;

    if (EVP_DigestUpdate(mdctx, salt, SALT_LENGTH) != 1)
        return -1;

    md = EVP_MD_CTX_md(mdctx);
    hash_len = EVP_MD_size(md);

    if (hash_len < 0 || hash == NULL)
        return -1;

    if (EVP_DigestFinal_ex(mdctx, hash, &md_len) != 1)
        return -1;

    EVP_MD_CTX_free(mdctx);

    for (i = 0; i < md_len; i++)
        hash[i] ^= salt[i];

    return 0;
}

int verify_password(const char *password, const unsigned char *salt, const unsigned char *stored_hash) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    int result;

    if ((result = hash_password(password, salt, hash)) != 0)
        return result;

    return memcmp(hash, stored_hash, EVP_MAX_MD_SIZE);
}

void store_user(const UserRecord *user) {
    FILE *file = fopen("users.db", "ab");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fwrite(user, sizeof(UserRecord), 1, file);
    fclose(file);
}

UserRecord* retrieve_user(const char *username) {
    UserRecord user;
    FILE *file = fopen("users.db", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    while (fread(&user, sizeof(UserRecord), 1, file)) {
        if (strncmp(user.username, username, sizeof(user.username)) == 0) {
            fclose(file);
            UserRecord *result = malloc(sizeof(UserRecord));
            memcpy(result, &user, sizeof(UserRecord));
            return result;
        }
    }
    fclose(file);
    return NULL;
}

void register_user() {
    char password[100];
    UserRecord user;

    printf("Enter username: ");
    scanf("%49s", user.username);

    printf("Enter password: ");
    scanf("%99s", password);

    if (generate_salt(user.salt, SALT_LENGTH) != 1) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }

    if (hash_password(password, user.salt, user.hash) != 0) {
        fprintf(stderr, "Error hashing password\n");
        exit(EXIT_FAILURE);
    }

    store_user(&user);
    printf("User registered successfully.\n");
}

void login_user() {
    char username[50], password[100];
    UserRecord *user;

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    user = retrieve_user(username);
    if (user == NULL) {
        printf("User not found.\n");
        return;
    }

    if (verify_password(password, user->salt, user->hash) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }

    free(user);
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Register\n2. Login\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                login_user();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}