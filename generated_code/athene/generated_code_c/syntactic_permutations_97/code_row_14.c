#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_BUFFER 256

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_BUFFER], password[MAX_BUFFER], firstname[MAX_BUFFER];
    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);
    printf("Enter first name: ");
    scanf("%255s", firstname);

    char query[MAX_BUFFER * 2];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username='%s'", mysql_real_escape_string(conn, username, strlen(username)));
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    int user_exists = atoi(row[0]);
    mysql_free_result(result);

    if (user_exists) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return 1;
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char password_hex[MAX_BUFFER * 2];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(password_hex + (i * 2), "%02x", hashed_password[i]);
    }

    sprintf(query, "INSERT INTO users (username, password, firstname) VALUES ('%s', '%s', '%s')",
            mysql_real_escape_string(conn, username, strlen(username)),
            mysql_real_escape_string(conn, password_hex, strlen(password_hex)),
            mysql_real_escape_string(conn, firstname, strlen(firstname)));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Registration succeeded.\n");
    mysql_close(conn);
    return 0;
}