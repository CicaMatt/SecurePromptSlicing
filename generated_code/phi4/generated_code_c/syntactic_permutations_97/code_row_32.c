#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define FIRST_NAME_LEN 50
#define LAST_NAME_LEN 50
#define EMAIL_LEN 100

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);
}

int username_exists(MYSQL *conn, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int exists = atoi(row[0]);
    mysql_free_result(result);

    return exists > 0;
}

int insert_user(MYSQL *conn, const char *username, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", 
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0);
    if (!conn) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char first_name[FIRST_NAME_LEN];
    char last_name[LAST_NAME_LEN];
    char email[EMAIL_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    if (username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    if (insert_user(conn, username, hashed_password)) {
        printf("Registration succeeded.\n");
    } else {
        printf("Registration failed.\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}