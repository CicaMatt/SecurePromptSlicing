#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "user_db"

void hash_password(const char* password, unsigned char* hashed) {
    // Simple hashing for demonstration; use a real library like OpenSSL in production
    for (int i = 0; i < strlen(password); ++i) {
        hashed[i] = password[i] ^ 0xAA;
    }
}

int check_username_exists(MYSQL *conn, const char* username) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    unsigned long length[1];
    char query[100];
    int exists = 0;

    sprintf(query, "SELECT COUNT(*) FROM users WHERE username=?");
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        return -1;
    }

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)username;
    bind[0].is_null = 0;
    bind[0].length = &length[0];
    length[0] = strlen(username);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        return -1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        return -1;
    }

    MYSQL_BIND result_bind[1];
    int count;
    unsigned long result_length[1];

    memset(result_bind, 0, sizeof(result_bind));
    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = (char*)&count;
    result_bind[0].is_null = 0;
    result_bind[0].length = &result_length[0];

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        fprintf(stderr, "mysql_stmt_bind_result() failed\n");
        return -1;
    }

    if (mysql_stmt_store_result(stmt)) {
        fprintf(stderr, "mysql_stmt_store_result() failed\n");
        return -1;
    }

    if (mysql_stmt_fetch(stmt) == 0 && count > 0) {
        exists = 1;
    }

    mysql_stmt_close(stmt);
    return exists;
}

int register_user(MYSQL *conn, const char* username, const char* password, 
                  const char* first_name, const char* last_name, const char* email) {

    unsigned char hashed_password[256];
    hash_password(password, hashed_password);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
        return -1;
    }

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[5], send[5];
    unsigned long length[5];

    const char* query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        return -1;
    }

    memset(bind, 0, sizeof(bind));
    memset(send, 0, sizeof(send));

    send[0].buffer_type = MYSQL_TYPE_STRING;
    send[0].buffer = (char*)username;
    length[0] = strlen(username);
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)username;
    bind[0].length = &length[0];

    send[1].buffer_type = MYSQL_TYPE_BLOB;
    send[1].buffer = hashed_password;
    length[1] = strlen((const char*)hashed_password);
    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = hashed_password;
    bind[1].length = &length[1];

    for (int i = 2; i < 5; ++i) {
        send[i].buffer_type = MYSQL_TYPE_STRING;
        send[i].buffer = (char*)((i == 2) ? first_name : ((i == 3) ? last_name : email));
        length[i] = strlen(send[i].buffer);
        bind[i].buffer_type = MYSQL_TYPE_STRING;
        bind[i].buffer = (char*)send[i].buffer;
        bind[i].length = &length[i];
    }

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        return -1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        return -1;
    }

    mysql_stmt_close(stmt);
    printf("Registration succeeded.\n");
    return 0;
}

int main(int argc, char *argv[]) {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        return 1;
    }

    char username[100], password[100], first_name[50], last_name[50], email[100];
    
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);
    printf("Enter Email: ");
    scanf("%s", email);

    register_user(conn, username, password, first_name, last_name, email);

    mysql_close(conn);
    return 0;
}