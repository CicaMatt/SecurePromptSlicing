#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "user_registration"

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)password, strlen(password), hashed);
}

int check_username_exists(MYSQL *conn, const char *username) {
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
    int count = atoi(row[0]);
    mysql_free_result(result);

    return count > 0 ? 1 : 0;
}

void register_user(MYSQL *conn, const char *username, unsigned char hashed_password[SHA256_DIGEST_LENGTH], 
                   const char *first_name, const char *last_name, const char *email) {
    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password_hash, first_name, last_name, email) "
                                   "VALUES ('%s', '%.*s', '%s', '%s', '%s')",
             username, SHA256_DIGEST_LENGTH, hashed_password,
             first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 1;
    }

    conn = mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];
    printf("Enter Username: ");
    scanf("%49s", username);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        printf("Enter Password: ");
        scanf("%49s", password);
        unsigned char hashed_password[SHA256_DIGEST_LENGTH];
        hash_password(password, hashed_password);

        printf("Enter First Name: ");
        scanf("%49s", first_name);
        printf("Enter Last Name: ");
        scanf("%49s", last_name);
        printf("Enter Email: ");
        scanf("%99s", email);

        register_user(conn, username, hashed_password, first_name, last_name, email);
        printf("Registration succeeded.\n");
    }

    mysql_close(conn);
    return 0;
}