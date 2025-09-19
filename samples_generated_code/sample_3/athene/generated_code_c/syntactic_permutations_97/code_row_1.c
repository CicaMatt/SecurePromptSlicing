#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_INPUT 256
#define SALT "somesalt"

void hash_password(const char *password, unsigned char *output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Update(&ctx, SALT, strlen(SALT));
    SHA256_Final(digest, &ctx);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf((char *)output + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_INPUT], password[MAX_INPUT], firstName[MAX_INPUT], lastName[MAX_INPUT], email[MAX_INPUT];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%255s", username);

    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT username FROM users WHERE username = ?")) {
        fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res))) {
        printf("Username already exists.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return 0;
    }
    mysql_free_result(res);

    printf("Enter password: ");
    scanf("%255s", password);
    hash_password(password, hashed_password);

    printf("Enter first name: ");
    scanf("%255s", firstName);

    printf("Enter last name: ");
    scanf("%255s", lastName);

    printf("Enter email: ");
    scanf("%255s", email);

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, hashed_password, firstName, lastName, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "MySQL insert error: %s\n", mysql_error(conn));
        exit(1);
    }

    printf("Registration succeeded.\n");

    mysql_close(conn);
    return 0;
}