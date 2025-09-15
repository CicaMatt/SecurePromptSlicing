#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);
}

int connect_database(MYSQL **conn) {
    *conn = mysql_init(NULL);

    if (*conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    if (mysql_real_connect(*conn, "localhost", "root", "", "webapp_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(*conn));
        mysql_close(*conn);
        return -1;
    }

    return 0;
}

int create_table(MYSQL *conn) {
    const char *create_table_query = 
        "CREATE TABLE IF NOT EXISTS users (" \
        "id INT AUTO_INCREMENT PRIMARY KEY, " \
        "username VARCHAR(50) UNIQUE NOT NULL, " \
        "password_hash CHAR(64) NOT NULL);";

    if (mysql_query(conn, create_table_query)) {
        fprintf(stderr, "Failed to create table: %s\n", mysql_error(conn));
        return -1;
    }

    return 0;
}

int register_user(MYSQL *conn, const char *username, unsigned char password_hash[SHA256_DIGEST_LENGTH]) {
    char insert_query[200];
    snprintf(insert_query, sizeof(insert_query), 
             "INSERT INTO users (username, password_hash) VALUES ('%s', '%s');",
             mysql_real_escape_string(conn, username, strlen(username)),
             mysql_real_escape_string(conn, (char *)password_hash, SHA256_DIGEST_LENGTH));

    if (mysql_query(conn, insert_query)) {
        fprintf(stderr, "Failed to register user: %s\n", mysql_error(conn));
        return -1;
    }

    return 0;
}

int main() {
    MYSQL *conn;
    if (connect_database(&conn) != 0) {
        exit(EXIT_FAILURE);
    }

    if (create_table(conn) != 0) {
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    if (register_user(conn, username, password_hash) != 0) {
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("User registered successfully!\n");

    mysql_close(conn);
    return 0;
}
