#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <sha256.h> // Assuming sha256.h is available for hashing

#define MAX_INPUT 100
#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"

void hash_password(const char *password, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_INPUT], password[MAX_INPUT], first_name[MAX_INPUT], last_name[MAX_INPUT], email[MAX_INPUT];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    printf("Enter first name: ");
    scanf("%99s", first_name);
    printf("Enter last name: ");
    scanf("%99s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    char query[256];
    sprintf(query, "SELECT username FROM users WHERE username = '%s'", username);
    mysql_query(conn, query);
    res = mysql_store_result(conn);

    if (mysql_num_rows(res) > 0) {
        printf("Username already exists.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }

    char hashed_password[65];
    hash_password(password, hashed_password);

    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')", username, hashed_password, first_name, last_name, email);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }

    printf("Registration succeeded.\n");
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}