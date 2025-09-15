#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int does_username_exist(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 0;
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "your_username", "your_password",
                            "your_database", 3306, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    // Formulate the query
    char query[256];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_store_result(conn);
    
    // Check for result
    row = mysql_fetch_row(res);
    int exists = row != NULL;

    mysql_free_result(res);
    mysql_close(conn);

    return exists ? 1 : 0; 
}

int main() {
    const char *username = "test_user";
    if (does_username_exist(username)) {
        printf("Username %s exists.\n", username);
    } else {
        printf("Username %s does not exist.\n", username);
    }
    
    return 0;
}
