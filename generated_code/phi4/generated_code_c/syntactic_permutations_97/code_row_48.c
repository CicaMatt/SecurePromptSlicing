#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define BUF_SIZE 256

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char*)password, strlen(password), output);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "registration_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[BUF_SIZE];
    char password_input[BUF_SIZE];
    char first_name[BUF_SIZE];
    char last_name[BUF_SIZE];
    char email[BUF_SIZE];

    printf("Enter Username: ");
    scanf("%255s", username);

    if (mysql_query(conn, "SELECT * FROM users WHERE username = '")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query_check[BUF_SIZE + 256];
    snprintf(query_check, sizeof(query_check), "SELECT * FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query_check)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
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

    printf("Enter Password: ");
    scanf("%255s", password_input);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password_input, hashed_password);

    char hashed_password_str[BUF_SIZE * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password_str[i * 2], "%02x", (unsigned int)hashed_password[i]);
    }

    printf("Enter First Name: ");
    scanf("%255s", first_name);

    printf("Enter Last Name: ");
    scanf("%255s", last_name);

    printf("Enter Email: ");
    scanf("%255s", email);

    char query_insert[BUF_SIZE * 6 + 512];
    snprintf(query_insert, sizeof(query_insert),
             "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, hashed_password_str, first_name, last_name, email);

    if (mysql_query(conn, query_insert)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Registration succeeded.\n");

    mysql_close(conn);
    return 0;
}