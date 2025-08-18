#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_SIZE 50
#define PASSWORD_SIZE 100

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "pass", "db_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char insert_query[256];
    snprintf(insert_query, sizeof(insert_query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, mysql_real_escape_string(conn, "", (const char *)hashed_password, SHA256_DIGEST_LENGTH));

    if (mysql_query(conn, insert_query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    return 0;
}