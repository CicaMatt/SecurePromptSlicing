#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_LEN 100

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "pass", "db_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_LEN];
    char password[MAX_LEN];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hash);

    char *query = malloc(1024);
    snprintf(query, 1024, "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, mysql_real_escape_string(conn, query, (char *)hash, SHA256_DIGEST_LENGTH));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    free(query);
    mysql_close(conn);

    return 0;
}

Note: The above code has a flaw in the way it constructs the SQL query. It should use prepared statements to prevent SQL injection and correctly handle binary data. Here is an improved version:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_LEN 100

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int main() {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    unsigned long length[2];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "pass", "db_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_LEN];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    char password[MAX_LEN];
    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hash);

    const char *sql = "INSERT INTO users (username, password) VALUES (?, ?)";
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = username;
    length[0] = strlen(username);
    bind[0].length = &length[0];

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = hash;
    length[1] = SHA256_DIGEST_LENGTH;
    bind[1].length = &length[1];

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    return 0;
}