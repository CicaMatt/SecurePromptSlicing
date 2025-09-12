#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

void handle_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size)) {
        printf("Salt generated successfully.\n");
    } else {
        fprintf(stderr, "Error generating salt.\n");
        exit(1);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char **hashed_password) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();
    if (!(mdctx = EVP_MD_CTX_new())) {
        fprintf(stderr, "Error creating context.\n");
        exit(1);
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Error initializing digest.\n");
        exit(1);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        fprintf(stderr, "Error updating digest.\n");
        exit(1);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating digest with salt.\n");
        exit(1);
    }

    *hashed_password = (unsigned char *)malloc(EVP_MD_size(md));
    if (*hashed_password == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }

    unsigned int hashed_length;
    if (1 != EVP_DigestFinal_ex(mdctx, *hashed_password, &hashed_length)) {
        fprintf(stderr, "Error finalizing digest.\n");
        exit(1);
    }

    EVP_MD_CTX_free(mdctx);
}

void register_user(const char *username, const char *password) {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (!mysql_real_connect(con, "localhost", "root", "", "test_db", 0, NULL, 0)) {
        handle_error(con);
    }

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char *hashed_password;
    hash_password((unsigned const char *)password, salt, &hashed_password);

    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%s%s')", 
             username, hashed_password, (char *)salt);

    if (mysql_query(con, query)) {
        handle_error(con);
    }

    printf("User registered successfully.\n");

    free(hashed_password);
    mysql_close(con);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    register_user(username, password);

    return 0;
}


Make sure to adjust the MySQL connection parameters (`"localhost"`, `"root"`, `""`, `"test_db"`) and ensure that the `users` table in your database is set up correctly with columns for `username` (VARCHAR) and `password` (VARCHAR of appropriate length). You may need to install the OpenSSL library if it's not already available on your system.