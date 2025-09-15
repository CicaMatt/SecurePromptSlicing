#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <mysql/mysql.h>

#define HASH_ALGORITHM EVP_sha256()
#define SALT_SIZE 16

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(EXIT_FAILURE);
}

int generate_salt(unsigned char *salt) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (!fp) return 0;
    size_t result = fread(salt, 1, SALT_SIZE, fp);
    fclose(fp);
    return result == SALT_SIZE ? 1 : 0;
}

int hash_password(const char *password, unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    unsigned int md_len;

    if (!(mdctx = EVP_MD_CTX_new())) return 0;

    if (1 != EVP_DigestInit_ex(mdctx, HASH_ALGORITHM, NULL)) goto err;
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) goto err;
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) goto err;
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &md_len)) goto err;

    EVP_MD_CTX_free(mdctx);
    return 1;

err:
    EVP_MD_CTX_free(mdctx);
    return 0;
}

void insert_into_database(MYSQL *conn, const char *username, const unsigned char *salt, const unsigned char *hash) {
    unsigned char hash_str[HASH_ALGORITHM->digest_size * 2 + 1];
    for (int i = 0; i < HASH_ALGORITHM->digest_size; ++i)
        sprintf((char *)&hash_str[i*2], "%02x", hash[i]);

    MYSQL_STMT *stmt;
    const char *query = "INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)";
    
    if ((stmt = mysql_stmt_init(conn)) == NULL) handle_error(conn);

    if (mysql_stmt_prepare(stmt, query, strlen(query))) handle_error(conn);

    MYSQL_BIND bind[3] = {
        {MYSQL_TYPE_VAR_STRING, (char *)&username, 0, 0, 0},
        {MYSQL_TYPE_BLOB, (char *)salt, SALT_SIZE, 0, 0},
        {MYSQL_TYPE_BLOB, (char *)hash_str, HASH_ALGORITHM->digest_size * 2, 0, 0}
    };

    if (mysql_stmt_bind_param(stmt, bind)) handle_error(conn);
    
    if (mysql_stmt_execute(stmt)) handle_error(conn);

    mysql_stmt_close(stmt);
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) 
        handle_error(conn);

    char username[100];
    unsigned char salt[SALT_SIZE], hash[EVP_MAX_MD_SIZE];

    printf("Enter username: ");
    scanf("%s", username);

    if (!generate_salt(salt))
        return EXIT_FAILURE;

    printf("Enter password: ");
    char password[100];
    scanf("%s", password);
    
    if (!hash_password(password, salt, hash))
        return EXIT_FAILURE;
    
    insert_into_database(conn, username, salt, hash);

    mysql_close(conn);
    return 0;
}
