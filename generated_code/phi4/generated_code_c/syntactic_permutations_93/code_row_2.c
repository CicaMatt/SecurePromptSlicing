#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 64

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[16];
    for (int i = 0; i < strlen(password); ++i)
        digest[i % 16] ^= password[i];

    for (int i = 0; i < 16; ++i) {
        sprintf(&hashed_password[i*2], "%02x", digest[i]);
    }
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[50];
    char password[50];
    char hashed_password[HASH_SIZE];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "testdb", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             mysql_real_escape_string(conn, username),
             mysql_real_escape_string(conn, hashed_password));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User inserted successfully.\n");

    mysql_close(conn);
    return 0;
}