#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 0;
    }
    
    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "your_username", "your_password", "your_database", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }
    
    // Execute query to check if the username exists
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }
    
    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    int count = atoi(row[0]);
    mysql_free_result(res);

    // Close the connection
    mysql_close(conn);
    
    // Return true (1) if username exists, false (0) otherwise
    return count > 0;
}

int main() {
    const char *username_to_check = "exampleUser";
    int result = check_username_exists(username_to_check);
    printf("Username exists: %d\n", result);
    return 0;
}
