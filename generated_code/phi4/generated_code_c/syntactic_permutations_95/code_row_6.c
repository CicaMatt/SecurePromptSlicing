#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE 20

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes for salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    unsigned int md_len;

    if (EVP_DigestInit_ex(mdctx = EVP_MD_CTX_new(), EVP_sha1(), NULL) != 1 ||
        EVP_DigestUpdate(mdctx, password, strlen((char *)password)) != 1 ||
        EVP_DigestUpdate(mdctx, salt, SALT_SIZE) != 1 ||
        EVP_DigestFinal_ex(mdctx, hash, &md_len) != 1)
    {
        fprintf(stderr, "Error hashing the password\n");
        exit(EXIT_FAILURE);
    }
}

void connect_database(MYSQL **conn) {
    *conn = mysql_init(NULL);
    if (*conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(*conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: Error: %s\n", mysql_error(*conn));
        mysql_close(*conn);
        exit(EXIT_FAILURE);
    }
}

void store_user(MYSQL *conn, const char *username, const unsigned char *salted_hash) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_ulonglong affected_rows;

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init(), out of memory\n");
        exit(EXIT_FAILURE);
    }

    const char *query = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = (char *)salted_hash;
    bind[1].length = HASH_SIZE + SALT_SIZE;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute(), INSERT failed\n");
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }
    
    affected_rows = mysql_stmt_affected_rows(stmt);
    printf("Inserted %llu rows.\n", affected_rows);

    mysql_stmt_close(stmt);
}

int main() {
    MYSQL *conn;
    connect_database(&conn);

    const char *username = "new_user";
    unsigned char password[] = "user_password";
    unsigned char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];

    generate_salt(salt, SALT_SIZE);
    hash_password(password, salt, hash);

    unsigned char salted_hash[HASH_SIZE + SALT_SIZE];
    memcpy(salted_hash, hash, HASH_SIZE);
    memcpy(salted_hash + HASH_SIZE, salt, SALT_SIZE);

    store_user(conn, username, salted_hash);

    mysql_close(conn);
    return 0;
}