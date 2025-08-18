#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "user_db"

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

char* hash_password(const char *password) {
    EVP_MD_CTX *ctx;
    unsigned char digest[SHA256_DIGEST_LENGTH];
    int len = SHA256_DIGEST_LENGTH;

    ctx = EVP_MD_CTX_new();
    if (!ctx)
        return NULL;

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) <= 0 ||
        EVP_DigestUpdate(ctx, password, strlen(password)) <= 0 ||
        EVP_DigestFinal_ex(ctx, digest, &len) <= 0) {
        EVP_MD_CTX_free(ctx);
        return NULL;
    }

    char *hashed_password = (char*)malloc(len + 1);
    if (!hashed_password) {
        EVP_MD_CTX_free(ctx);
        return NULL;
    }
    
    for (int i = 0; i < len; i++)
        sprintf(hashed_password + (i*2), "%02x", digest[i]);

    hashed_password[len] = '\0';
    EVP_MD_CTX_free(ctx);

    return hashed_password;
}

void register_user(const char *username, const char *password) {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!conn)
        handle_error(conn);

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL)
        handle_error(conn);

    char *hashed_password = hash_password(password);
    if (!hashed_password) {
        fprintf(stderr, "Password hashing failed.\n");
        mysql_close(conn);
        exit(1);
    }

    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, hashed_password);
    
    if (mysql_query(conn, query)) {
        handle_error(conn);
    }
    
    free(hashed_password);
    printf("User registered successfully!\n");

    mysql_close(conn);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    register_user(username, password);

    return 0;
}