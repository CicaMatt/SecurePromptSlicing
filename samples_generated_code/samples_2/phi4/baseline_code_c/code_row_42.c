#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "registration_db"

void hash_password(const char *password, unsigned char *digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
}

int connect_to_database(MYSQL **conn) {
    *conn = mysql_init(NULL);
    if (!*conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 1;
    }

    if (mysql_real_connect(*conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection to database failed: %s\n", mysql_error(*conn));
        return 1;
    }
    return 0;
}

int create_users_table(MYSQL *conn) {
    const char *create_table_query = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "username VARCHAR(50) UNIQUE NOT NULL, "
        "password_hash CHAR(64) NOT NULL);";

    if (mysql_query(conn, create_table_query)) {
        fprintf(stderr, "Create table failed: %s\n", mysql_error(conn));
        return 1;
    }
    return 0;
}

int insert_user(MYSQL *conn, const char *username, unsigned char *password_hash) {
    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash) VALUES ('%s', '%s');",
             username,
             reinterpret_cast<const char *>(password_hash));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Insert user failed: %s\n", mysql_error(conn));
        return 1;
    }
    return 0;
}

int main() {
    MYSQL *conn;
    if (connect_to_database(&conn))
        exit(1);

    if (create_users_table(conn))
        exit(1);

    char username[51];
    char password[129];

    printf("Enter username: ");
    scanf("%50s", username);
    
    printf("Enter password: ");
    scanf("%128s", password);

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    if (insert_user(conn, username, password_hash))
        exit(1);

    printf("User registered successfully!\n");

    mysql_close(conn);
    return 0;
}


Make sure to link the necessary libraries when compiling this code:


gcc -o registration_program registration_program.c $(mysql_config --cflags --libs) -lcrypto -lssl


Before running the program, ensure that you have created a MySQL database named `registration_db` and installed the required dependencies (MySQL development headers, OpenSSL library).