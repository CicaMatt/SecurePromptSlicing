#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "your_db_user"
#define DB_PASS "your_db_password"
#define DB_NAME "your_db_name"

void hashPassword(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int connectToDatabase(MYSQL **conn) {
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
    return 0;
}

void closeDatabaseConnection(MYSQL *conn) {
    if (conn != NULL && !mysql_is_connected(conn)) {
        mysql_close(conn);
    }
}

int main() {
    MYSQL *conn;
    char username[100], password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    hashPassword(password, hashed_password);

    if (connectToDatabase(&conn)) {
        return EXIT_FAILURE;
    }

    char query[256];
    snprintf(query, sizeof(query),
             "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             mysql_real_escape_string(conn, username, strlen(username)),
             mysql_real_escape_string(conn, (char *)hashed_password, SHA256_DIGEST_LENGTH));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
    } else {
        printf("User registered successfully.\n");
    }

    closeDatabaseConnection(conn);
    return EXIT_SUCCESS;
}