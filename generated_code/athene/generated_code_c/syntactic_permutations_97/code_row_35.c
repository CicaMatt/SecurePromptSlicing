#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASSWORD "yourpassword"
#define DB_NAME "yourdb"

unsigned char *hash_password(const char *password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), digest);
    return digest;
}

int check_username_exists(MYSQL *conn, const char *username) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT username FROM users WHERE username = ?")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    if (mysql_stmt_prepare(mysql_stmt_init(conn), "SELECT username FROM users WHERE username = ?", 47) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(mysql_stmt_init(conn), bind) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    if (mysql_stmt_execute(mysql_stmt_init(conn)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    mysql_free_result(res);
    mysql_stmt_close(mysql_stmt_init(conn));

    if (row == NULL) {
        return 0; // Username does not exist
    }
    return 1; // Username exists
}

void register_user(MYSQL *conn, const char *username, const char *password, const char *firstname, const char *lastname, const char *email) {
    unsigned char *hashed_password = hash_password(password);
    char hashed_password_str[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password_str + i * 2, "%02x", (unsigned int)hashed_password[i]);
    }

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[5];

    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, "INSERT INTO users (username, password, firstname, lastname, email) VALUES (?, ?, ?, ?, ?)", 104) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = hashed_password_str;

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)firstname;

    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (char *)lastname;

    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = (char *)email;

    if (mysql_stmt_bind_param(stmt, bind) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    mysql_stmt_close(stmt);
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char username[50], password[50], firstname[50], lastname[50], email[50];

    printf("Enter username: ");
    scanf("%49s", username);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return 1;
    }

    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", firstname);

    printf("Enter last name: ");
    scanf("%49s", lastname);

    printf("Enter email: ");
    scanf("%49s", email);

    register_user(conn, username, password, firstname, lastname, email);
    printf("Registration succeeded.\n");

    mysql_close(conn);
    return 0;
}