#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "users_db"

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char*)password, strlen(password), hashed);
}

int username_exists(MYSQL *conn, const char *username) {
    char query[128];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    return count > 0 ? 1 : 0;
}

int insert_user(MYSQL *conn, const char *username, const unsigned char hashed_password[SHA256_DIGEST_LENGTH], 
                const char *first_name, const char *last_name, const char *email) {
    char query[512];
    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
            username, 
            mysql_real_escape_string(conn, (char*)hashed_password, SHA256_DIGEST_LENGTH),
            mysql_real_escape_string(conn, first_name, strlen(first_name)),
            mysql_real_escape_string(conn, last_name, strlen(last_name)),
            mysql_real_escape_string(conn, email, strlen(email)));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];
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

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    if (username_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        if (insert_user(conn, username, hashed_password, first_name, last_name, email) == 0) {
            printf("Registration succeeded.\n");
        } else {
            printf("Failed to register user.\n");
        }
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}