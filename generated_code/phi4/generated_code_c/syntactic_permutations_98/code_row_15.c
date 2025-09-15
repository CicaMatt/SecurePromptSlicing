#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_INPUT 256

void hash_password(const char *password, unsigned char digest[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)password, strlen(password), digest);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *host = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database_name = "registration_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database_name, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char username[MAX_INPUT], input_password[MAX_INPUT];

    printf("Enter username: ");
    fgets(username, MAX_INPUT, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    fgets(input_password, MAX_INPUT, stdin);
    input_password[strcspn(input_password, "\n")] = 0; // Remove newline

    hash_password(input_password, hashed_password);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Registration successful.\n");
    }

    mysql_close(conn);
    return 0;
}
