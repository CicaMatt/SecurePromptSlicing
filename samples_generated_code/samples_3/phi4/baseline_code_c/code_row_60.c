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
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(output, &sha256);
}

int connect_to_database(MYSQL **conn) {
    *conn = mysql_init(NULL);

    if (*conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 0;
    }

    if (mysql_real_connect(*conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(*conn));
        mysql_close(*conn);
        return 0;
    }
    return 1;
}

int check_username_exists(MYSQL *conn, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", mysql_real_escape_string(conn, (char *)username));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to check username: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "Failed to store result: %s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    return (count > 0) ? 1 : 0;
}

int insert_user(MYSQL *conn, const char *username, unsigned char hashed_password[SHA256_DIGEST_LENGTH], const char *first_name, const char *last_name, const char *email) {
    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             mysql_real_escape_string(conn, (char *)username),
             mysql_real_escape_string(conn, (char *)hashed_password, SHA256_DIGEST_LENGTH * 2 + 1),
             mysql_real_escape_string(conn, (char *)first_name),
             mysql_real_escape_string(conn, (char *)last_name),
             mysql_real_escape_string(conn, (char *)email));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to insert user: %s\n", mysql_error(conn));
        return 0;
    }
    return 1;
}

int main() {
    MYSQL *conn;
    char username[50], password[50], first_name[50], last_name[50], email[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    if (!connect_to_database(&conn)) {
        return EXIT_FAILURE;
    }

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

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        hash_password(password, hashed_password);
        if (insert_user(conn, username, hashed_password, first_name, last_name, email)) {
            printf("Registration succeeded.\n");
        } else {
            printf("Failed to register user.\n");
        }
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}