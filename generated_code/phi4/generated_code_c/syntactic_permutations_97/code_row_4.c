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

void hash_password(const char *password, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)password, strlen(password), hash);
}

int is_username_exists(MYSQL *conn, const char *username) {
    char query[256];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    return count > 0 ? 1 : 0;
}

int register_user(MYSQL *conn, const char *username, const unsigned char hash[SHA256_DIGEST_LENGTH], 
                  const char *first_name, const char *last_name, const char *email) {
    char query[512];
    sprintf(query, "INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
            username,
            mysql_real_escape_string(conn, (char *)hash, SHA256_DIGEST_LENGTH),
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
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed.\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "password", "test_db", 3306, NULL, 0);
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

    if (is_username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    if (register_user(conn, username, hash, first_name, last_name, email) == 0) {
        printf("Registration succeeded.\n");
    } else {
        printf("Registration failed.\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}