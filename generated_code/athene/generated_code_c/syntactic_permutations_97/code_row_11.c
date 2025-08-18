#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "testdb"

void hash_password(const char *password, unsigned char *output) {
    SHA1((unsigned char *)password, strlen(password), output);
}

int check_username_exists(MYSQL *conn, const char *username) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    int exists = 0;

    if (mysql_query(conn, "SELECT username FROM users WHERE username = '") != 0) {
        mysql_real_escape_string(conn, (char *)username, username, strlen(username));
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL) {
        exists = 1;
    }
    mysql_free_result(res);
    return exists;
}

int register_user(MYSQL *conn, const char *username, const unsigned char *password_hash, const char *first_name, const char *last_name, const char *email) {
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             mysql_real_escape_string(conn, username, username, strlen(username)),
             mysql_real_escape_string(conn, (char *)password_hash, (const char *)password_hash, 20),
             mysql_real_escape_string(conn, first_name, first_name, strlen(first_name)),
             mysql_real_escape_string(conn, last_name, last_name, strlen(last_name)),
             mysql_real_escape_string(conn, email, email, strlen(email)));

    if (mysql_query(conn, query) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char username[100], password[100], first_name[100], last_name[100], email[100];
    unsigned char password_hash[20];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        hash_password(password, password_hash);
        if (register_user(conn, username, password_hash, first_name, last_name, email) == 0) {
            printf("Registration succeeded.\n");
        } else {
            printf("Registration failed.\n");
        }
    }

    mysql_close(conn);
    return 0;
}