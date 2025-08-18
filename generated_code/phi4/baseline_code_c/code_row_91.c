#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "userdb"

void hash_password(const char *password, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int connect_to_database(MYSQL **conn) {
    *conn = mysql_init(NULL);
    if (!*conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 1;
    }
    
    if (!mysql_real_connect(*conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(*conn));
        mysql_close(*conn);
        return 1;
    }

    return 0;
}

int create_table(MYSQL *conn) {
    const char *query = "CREATE TABLE IF NOT EXISTS users ("
                        "id INT AUTO_INCREMENT PRIMARY KEY,"
                        "username VARCHAR(50) UNIQUE NOT NULL,"
                        "password_hash CHAR(64) NOT NULL);";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    return 0;
}

int insert_user(MYSQL *conn, const char *username, unsigned char *password_hash) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_ulonglong affected_rows;

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return 1;
    }

    const char *query = "INSERT INTO users (username, password_hash) VALUES (?, ?);";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = (char *)password_hash;
    bind[1].buffer_length = SHA256_DIGEST_LENGTH;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    affected_rows = mysql_stmt_affected_rows(stmt);
    mysql_stmt_close(stmt);

    return affected_rows > 0 ? 0 : 1;
}

int main() {
    MYSQL *conn;
    if (connect_to_database(&conn)) {
        exit(EXIT_FAILURE);
    }
    
    create_table(conn);
    
    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    if (insert_user(conn, username, password_hash)) {
        fprintf(stderr, "Failed to insert user\n");
    } else {
        printf("User registered successfully!\n");
    }

    mysql_close(conn);
    return 0;
}