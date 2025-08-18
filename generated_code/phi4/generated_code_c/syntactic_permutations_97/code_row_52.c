#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

#define PASSWORD_HASH_LEN 32

void hash_password(const char *password, unsigned char *hash) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_sha256();

    if (!EVP_DigestInit_ex(mdctx, md, NULL)) {
        exit(EXIT_FAILURE);
    }

    if (!EVP_DigestUpdate(mdctx, password, strlen(password))) {
        exit(EXIT_FAILURE);
    }

    unsigned int len;
    if (!EVP_DigestFinal_ex(mdctx, hash, &len)) {
        exit(EXIT_FAILURE);
    }
    EVP_MD_CTX_free(mdctx);

    for (int i = 0; i < PASSWORD_HASH_LEN; ++i) {
        sprintf((char*)&hash[i], "%02x", hash[i]);
    }
}

void register_user(const char *username, const char *password, const char *first_name, 
                   const char *last_name, const char *email, MYSQL *conn) {

    unsigned char hash[PASSWORD_HASH_LEN + 1];
    memset(hash, 0, sizeof(hash));
    hash_password(password, hash);

    if (mysql_query(conn, "SELECT username FROM users WHERE username = ?")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    
    char *query = "SELECT username FROM users WHERE username = ?";
    if (!mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }
    
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    char user_name[100];
    strncpy(user_name, username, sizeof(user_name) - 1);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)user_name;
    bind[0].buffer_length = strlen(username);
    
    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }
    
    MYSQL_BIND result;
    memset(&result, 0, sizeof(result));

    my_ulonglong affected_rows = mysql_stmt_affected_rows(stmt);

    if (affected_rows > 0) {
        printf("Username already exists.\n");
        mysql_stmt_close(stmt);
        return;
    }

    char insert_query[] = "INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    stmt = mysql_stmt_init(conn);

    if (!mysql_stmt_prepare(stmt, insert_query, strlen(insert_query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    MYSQL_BIND bind_insert[5];
    memset(bind_insert, 0, sizeof(bind_insert));

    bind_insert[0].buffer_type = MYSQL_TYPE_STRING;
    bind_insert[0].buffer = (char*)user_name;
    bind_insert[0].buffer_length = strlen(username);

    char pass_hash[PASSWORD_HASH_LEN + 1];
    strncpy(pass_hash, hash, PASSWORD_HASH_LEN);
    
    bind_insert[1].buffer_type = MYSQL_TYPE_STRING;
    bind_insert[1].buffer = (char*)pass_hash;
    bind_insert[1].buffer_length = strlen(pass_hash);

    bind_insert[2].buffer_type = MYSQL_TYPE_STRING;
    bind_insert[2].buffer = (char*)first_name;
    bind_insert[2].buffer_length = strlen(first_name);
    
    bind_insert[3].buffer_type = MYSQL_TYPE_STRING;
    bind_insert[3].buffer = (char*)last_name;
    bind_insert[3].buffer_length = strlen(last_name);

    bind_insert[4].buffer_type = MYSQL_TYPE_STRING;
    bind_insert[4].buffer = (char*)email;
    bind_insert[4].buffer_length = strlen(email);

    if (mysql_stmt_bind_param(stmt, bind_insert)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }
    
    printf("User registered successfully.\n");

    mysql_stmt_close(stmt);
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    const char *username = "newuser";
    const char *password = "securepassword123";
    const char *first_name = "John";
    const char *last_name = "Doe";
    const char *email = "john.doe@example.com";

    register_user(username, password, first_name, last_name, email, conn);

    mysql_close(conn);
    return 0;
}