#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define BUF_SIZE 256

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *) password, strlen(password), output);
}

int username_exists(MYSQL *conn, const char *username) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[BUF_SIZE];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    int count = atoi(row[0]);

    mysql_free_result(res);
    return count > 0;
}

int register_user(MYSQL *conn, const char *username, unsigned char hashed_password[SHA256_DIGEST_LENGTH], 
                  const char *first_name, const char *last_name, const char *email) {
    
    char query[BUF_SIZE + SHA256_DIGEST_LENGTH];
    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')", 
            username, hashed_password, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }
    
    char username[BUF_SIZE], password[BUF_SIZE], first_name[BUF_SIZE], last_name[BUF_SIZE], email[BUF_SIZE];

    printf("Enter Username: ");
    scanf("%255s", username);

    if (username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Enter Password: ");
    scanf("%255s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    printf("Enter First Name: ");
    scanf("%255s", first_name);

    printf("Enter Last Name: ");
    scanf("%255s", last_name);

    printf("Enter Email: ");
    scanf("%255s", email);

    if (register_user(conn, username, hashed_password, first_name, last_name, email) == 0) {
        printf("Registration succeeded.\n");
    } else {
        fprintf(stderr, "Failed to register user.\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}