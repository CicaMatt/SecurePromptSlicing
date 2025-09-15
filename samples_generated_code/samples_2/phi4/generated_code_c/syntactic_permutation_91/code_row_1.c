#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "webapp"

void hash_password(const char* password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int connect_db(MYSQL **conn) {
    *conn = mysql_init(NULL);
    if (*conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }
    
    if (mysql_real_connect(*conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(*conn));
        mysql_close(*conn);
        return 1;
    }
    
    printf("Connected to database successfully!\n");
    return 0;
}

int create_table(MYSQL *conn) {
    const char *query = "CREATE TABLE IF NOT EXISTS users ("
                        "id INT AUTO_INCREMENT PRIMARY KEY, "
                        "username VARCHAR(50) NOT NULL UNIQUE, "
                        "password_hash BINARY(32))";
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to create table: %s\n", mysql_error(conn));
        return 1;
    }
    
    printf("Table 'users' created or already exists.\n");
    return 0;
}

int register_user(MYSQL *conn, const char* username, unsigned char password_hash[SHA256_DIGEST_LENGTH]) {
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return 1;
    }
    
    const char *query = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return 1;
    }
    
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_BINARY;
    bind[1].buffer = (char *)password_hash;
    bind[1].buffer_length = SHA256_DIGEST_LENGTH;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return 1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return 1;
    }
    
    printf("User '%s' registered successfully.\n", username);
    mysql_stmt_close(stmt);
    return 0;
}

int main(int argc, char *argv[]) {
    MYSQL *conn;
    if (connect_db(&conn)) {
        return 1;
    }

    create_table(conn);

    const char *username = "testuser";
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    
    printf("Enter password: ");
    char password[100];
    scanf("%99s", password);
    
    hash_password(password, password_hash);

    register_user(conn, username, password_hash);

    mysql_close(conn);
    return 0;
}
