#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 64

void hash_password(const char* input, char* output) {
    unsigned long hash = 5381;
    int c;

    while ((c = *input++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    snprintf(output, HASH_SIZE, "%lu", hash);
}

int main() {
    MYSQL* conn;
    MYSQL_STMT* stmt;
    const char* server = "localhost";
    const char* user = "root"; // Adjust the username
    const char* password = ""; // Adjust the password
    const char* database = "testdb";

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        mysql_close(conn);
        exit(1);
    }

    const char* query = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    char username[256];
    char password_input[256];
    char hashed_password[HASH_SIZE];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password_input, sizeof(password_input), stdin);
    password_input[strcspn(password_input, "\n")] = '\0';

    hash_password(password_input, hashed_password);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)username;
    bind[0].buffer_length = strlen(username);
    mysql_stmt_bind_param(stmt, bind);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = hashed_password;
    bind[1].buffer_length = strlen(hashed_password);
    mysql_stmt_bind_param(stmt, bind + 1);

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    } else {
        printf("User inserted successfully.\n");
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);
    
    return 0;
}