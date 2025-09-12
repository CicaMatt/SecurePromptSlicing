#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define NAME_LEN 50
#define EMAIL_LEN 100

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "db_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[USERNAME_LEN], password[PASSWORD_LEN], first_name[NAME_LEN], last_name[NAME_LEN], email[EMAIL_LEN];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    char query[256];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username='%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res && mysql_num_rows(res) > 0) {
        printf("Username already exists.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char hashed_password_str[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password_str + (i * 2), "%02x", hashed_password[i]);
    }

    snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, hashed_password_str, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Registration succeeded.\n");

    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}