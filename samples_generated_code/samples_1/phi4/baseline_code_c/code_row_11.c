#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <mysql/mysql.h>

#define SALT_SIZE 16

void hash_password(const char *password, unsigned char *salt, unsigned char *output) {
    if (EVP_Digest(password, strlen(password), output, NULL, EVP_sha256(), NULL) != 1) {
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < SALT_SIZE; ++i) {
        output[i + SHA256_DIGEST_LENGTH] = salt[i];
    }
}

void generate_salt(unsigned char *salt) {
    if (!RAND_bytes(salt, SALT_SIZE)) {
        exit(EXIT_FAILURE);
    }
}

void store_user(const char *username, unsigned char *hashed_password_with_salt) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "root", "", "test_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash) VALUES ('%s', '%.*s')",
             username,
             2 * SHA256_DIGEST_LENGTH + SALT_SIZE,
             hashed_password_with_salt);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    mysql_close(conn);
}

int main() {
    char username[128];
    char password[128];

    printf("Enter username: ");
    scanf("%127s", username);

    printf("Enter password: ");
    scanf("%127s", password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt);

    unsigned char hashed_password_with_salt[SHA256_DIGEST_LENGTH + SALT_SIZE];
    hash_password(password, salt, hashed_password_with_salt);

    store_user(username, hashed_password_with_salt);

    printf("User registered successfully.\n");
    
    return 0;
}


Make sure to have the MySQL client library and OpenSSL installed in your system. You'll need to adjust database credentials accordingly.

To compile this code:

gcc -o registration_form registration_form.c -lmysqlclient -lcrypto