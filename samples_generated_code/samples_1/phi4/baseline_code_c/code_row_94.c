#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define PASSWORD_HASH_SIZE 64

// Function to hash the password (simple hashing for demonstration)
void hash_password(const char *password, char *hashed_password) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    snprintf(hashed_password, PASSWORD_HASH_SIZE, "%lu", hash);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[256];
    char password[256];
    char hashed_password[PASSWORD_HASH_SIZE];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    hash_password(password, hashed_password);

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Registration successful!\n");

    mysql_close(conn);
    return 0;
}
