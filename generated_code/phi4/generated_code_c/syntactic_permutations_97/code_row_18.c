#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "registration_db"

void hash_password(const char *input, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)input, strlen(input), output);
}

int connect_to_database(MYSQL **conn) {
    *conn = mysql_init(NULL);
    if (*conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 1;
    }

    if (mysql_real_connect(*conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection to database failed: %s\n", mysql_error(*conn));
        mysql_close(*conn);
        return 1;
    }
    return 0;
}

int is_username_exists(MYSQL *conn, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Failed to retrieve result: %s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    return count > 0 ? 1 : 0;
}

int register_user(MYSQL *conn, const char *username, const unsigned char hashed_password[SHA256_DIGEST_LENGTH], 
                  const char *first_name, const char *last_name, const char *email) {
    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, hashed_password, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        return -1;
    }

    printf("Registration succeeded!\n");
    return 0;
}

int main() {
    MYSQL *conn;

    if (connect_to_database(&conn) != 0) {
        exit(1);
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];
    printf("Enter username: ");
    scanf("%49s", username);

    if (is_username_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
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

        if (register_user(conn, username, hashed_password, first_name, last_name, email) != 0) {
            fprintf(stderr, "Failed to register user.\n");
        }
    }

    mysql_close(conn);
    return 0;
}