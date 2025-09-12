#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

// Function to initialize MySQL connection
MYSQL* init_mysql_connection() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "username", "password",
                           "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    
    return conn;
}

// Function to check if the user is a moderator
int is_user_moderator(MYSQL *conn, const char* username) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    int result = 0;

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username=?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    memset(bind, 0, sizeof(bind));

    // Bind the input parameter
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)username;
    bind[0].buffer_length = strlen(username);
    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    // Execute the statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    MYSQL_BIND result_bind[1];
    int is_moderator;

    memset(result_bind, 0, sizeof(result_bind));

    // Bind the output parameter
    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = (char *)&is_moderator;
    result_bind[0].length = &result;

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        fprintf(stderr, "mysql_stmt_bind_result() failed: %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    // Fetch the result
    if (!mysql_stmt_fetch(stmt)) {
        result = 1; // User is a moderator if query returns true
    } else {
        fprintf(stderr, "mysql_stmt_fetch() failed: %s\n", mysql_stmt_error(stmt));
    }

    mysql_stmt_close(stmt);

    return is_moderator ? 1 : 0;
}

// Simulated web route function
void handle_request(const char* username) {
    MYSQL *conn = init_mysql_connection();
    
    if (is_user_moderator(conn, username)) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }

    mysql_close(conn);
}

int main() {
    handle_request("testuser"); // Replace "testuser" with the actual username to check
    return 0;
}