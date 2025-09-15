#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 64

void hash_password(const char *password, char *hashed) {
    unsigned char digest[16];
    int len = snprintf(hashed, HASH_SIZE, "%s", password); // Simple hashing simulation
    for (int i = 0; i < sizeof(digest); ++i) {
        digest[i] = (unsigned char)(len + i);
    }
    for (int i = 0; i < sizeof(digest); ++i) {
        snprintf(&hashed[i * 2], HASH_SIZE - i * 2, "%02x", digest[i]);
    }
}

void insert_user(MYSQL *conn, const char *username, const char *hashed_password) {
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[64];
    char password[64];

    printf("Enter username: ");
    scanf("%63s", username);

    printf("Enter password: ");
    scanf("%63s", password);

    char hashed_password[HASH_SIZE];
    hash_password(password, hashed_password);
    
    insert_user(conn, username, hashed_password);

    mysql_close(conn);
    return EXIT_SUCCESS;
}
