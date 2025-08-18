#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "openssl/sha.h"

#define USERNAME_SIZE 50
#define PASSWORD_SIZE 50
#define FIRST_NAME_SIZE 50
#define LAST_NAME_SIZE 50
#define EMAIL_SIZE 100

void hash_password(const char* password, unsigned char* hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int register_user(MYSQL *conn, const char *username, const char *password, 
                  const char *first_name, const char *last_name, const char *email) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    char query_username_check[256];
    sprintf(query_username_check, "SELECT username FROM users WHERE username = '%s';", username);
    if (mysql_query(conn, query_username_check)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result || mysql_num_rows(result) > 0) {
        printf("Username already exists.\n");
        if (result) mysql_free_result(result);
        return 0;
    }
    mysql_free_result(result);

    char query_insert[512];
    sprintf(query_insert, "INSERT INTO users (username, password_hash, first_name, last_name, email) "
                         "VALUES ('%s', '%s', '%s', '%s', '%s');", 
            username, 
            hash, 
            first_name, 
            last_name, 
            email);

    if (mysql_query(conn, query_insert)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    printf("Registration succeeded.\n");
    return 1;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[USERNAME_SIZE], password[PASSWORD_SIZE], first_name[FIRST_NAME_SIZE],
         last_name[LAST_NAME_SIZE], email[EMAIL_SIZE];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    if (register_user(conn, username, password, first_name, last_name, email) < 0) {
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}