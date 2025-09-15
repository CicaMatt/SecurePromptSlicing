#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>
#include <time.h>

void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Final(hash, &sha256);
}

void register_user(const char *name, const char *password) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "user_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char salt[9];
    generate_salt(salt, 8);
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, salt, hash);

    char hashed_password[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i*2], "%02x", hash[i]);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (name, password) VALUES ('%s', '%s%s')",
             name, hashed_password, salt);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
}

void verify_user(const char *name, const char *password) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "user_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE name='%s'", name);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    if (!row) {
        printf("User not found.\n");
        mysql_free_result(result);
        mysql_close(conn);
        return;
    }

    char stored_hash[2 * SHA256_DIGEST_LENGTH + 9];
    strncpy(stored_hash, row[0], sizeof(stored_hash));
    stored_hash[sizeof(stored_hash) - 1] = '\0';

    unsigned char hash[SHA256_DIGEST_LENGTH];
    char salt[9];
    memcpy(salt, &stored_hash[2 * SHA256_DIGEST_LENGTH], 8);
    salt[8] = '\0';
    hash_password(password, salt, hash);

    char hashed_input_password[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_input_password[i*2], "%02x", hash[i]);
    }

    if (strncmp(hashed_input_password, stored_hash, 2 * SHA256_DIGEST_LENGTH) == 0) {
        printf("Password verified successfully.\n");
    } else {
        printf("Incorrect password.\n");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    srand(time(NULL));

    char name[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", name);

    printf("Enter password: ");
    scanf("%99s", password);

    register_user(name, password);

    printf("\nEnter username to verify: ");
    scanf("%99s", name);

    printf("Enter password to verify: ");
    scanf("%99s", password);

    verify_user(name, password);

    return 0;
}
