#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <mysql/mysql.h>

#define SALT_SIZE 16

void hash_password(const char *password, unsigned char salt[SALT_SIZE], unsigned char hashed_password[32]) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *alg = EVP_sha256();
    
    mdctx = EVP_MD_CTX_new();
    RAND_bytes(salt, SALT_SIZE);
    EVP_DigestInit_ex(mdctx, alg, NULL);
    EVP_DigestUpdate(mdctx, salt, SALT_SIZE);
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestFinal_ex(mdctx, hashed_password, NULL);
    EVP_MD_CTX_free(mdctx);
}

void store_user(const char *username, const unsigned char *hashed_password) {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    unsigned char salt[SALT_SIZE];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    stmt = mysql_stmt_init(conn);
    const char *query = "INSERT INTO users (username, password) VALUES (?, ?)";
    if (!mysql_stmt_prepare(stmt, query, strlen(query))) {
        unsigned char hashed_password_full[40];
        memcpy(hashed_password_full, salt, SALT_SIZE);
        memcpy(hashed_password_full + SALT_SIZE, hashed_password, 32);

        memset(bind, 0, sizeof(bind));
        
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = (char *)username;
        bind[0].length = strlen(username) + 1;

        bind[1].buffer_type = MYSQL_TYPE_BLOB;
        bind[1].buffer = hashed_password_full;
        bind[1].buffer_length = sizeof(hashed_password_full);

        mysql_stmt_bind_param(stmt, bind);
        
        if (mysql_stmt_execute(stmt)) {
            fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Prepare statement failed: %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);
}

void register_user() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    unsigned char hashed_password[32];
    unsigned char salt[SALT_SIZE];

    hash_password(password, salt, hashed_password);

    store_user(username, hashed_password);
}

int main() {
    register_user();
    return 0;
}