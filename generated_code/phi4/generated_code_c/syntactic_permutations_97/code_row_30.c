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

void hash_password(const char* password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int check_username_exists(MYSQL *conn, const char *username) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    unsigned long length[1] = {0};
    my_bool is_null[1] = {0};

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return 1;
    }

    const char *query = "SELECT COUNT(*) FROM users WHERE username = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        return 1;
    }

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].is_null = &is_null[0];
    bind[0].length = &length[0];

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        return 1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        return 1;
    }

    MYSQL_BIND result_bind[1];
    unsigned long result_length[1] = {0};
    my_bool result_is_null[1] = {0};
    int count;

    memset(result_bind, 0, sizeof(result_bind));
    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = (char *)&count;
    result_bind[0].is_null = &result_is_null[0];
    result_bind[0].length = &result_length[0];

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        fprintf(stderr, "mysql_stmt_bind_result() failed\n");
        return 1;
    }

    if (mysql_stmt_store_result(stmt)) {
        fprintf(stderr, "mysql_stmt_store_result() failed\n");
        return 1;
    }

    if (mysql_stmt_fetch(stmt)) {
        fprintf(stderr, "mysql_stmt_fetch() failed\n");
        return 1;
    }

    mysql_stmt_close(stmt);
    return count > 0;
}

int register_user(MYSQL *conn, const char *username, unsigned char hashed_password[SHA256_DIGEST_LENGTH], 
                  const char *first_name, const char *last_name, const char *email) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[5];
    unsigned long length[5] = {0};
    my_bool is_null[5] = {0};

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return 1;
    }

    const char *query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        return 1;
    }

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].is_null = &is_null[0];
    bind[0].length = &length[0];

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = hashed_password;
    bind[1].buffer_length = SHA256_DIGEST_LENGTH;
    bind[1].is_null = &is_null[1];
    bind[1].length = &length[1];

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)first_name;
    bind[2].is_null = &is_null[2];
    bind[2].length = &length[2];

    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (char *)last_name;
    bind[3].is_null = &is_null[3];
    bind[3].length = &length[3];

    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = (char *)email;
    bind[4].is_null = &is_null[4];
    bind[4].length = &length[4];

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        return 1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        return 1;
    }

    mysql_stmt_close(stmt);
    return 0;
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[USERNAME_LEN], password[PASSWORD_LEN], first_name[FIRST_NAME_LEN], 
         last_name[LAST_NAME_LEN], email[EMAIL_LEN];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return 1;
    }

    printf("Enter password: ");
    scanf("%49s", password);
    hash_password(password, hashed_password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    if (register_user(conn, username, hashed_password, first_name, last_name, email)) {
        printf("Registration failed.\n");
    } else {
        printf("Registration succeeded.\n");
    }

    mysql_close(conn);
    return 0;
}