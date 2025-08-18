#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int does_username_exist(const char *hostname, const char *username, const char *password, const char *database_name, const char *table_name, const char *column_name, const char *user_to_check) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, hostname, username, password, database_name, 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to MySQL: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT EXISTS(SELECT 1 FROM %s WHERE %s='%s')", table_name, column_name, user_to_check);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    int exists = atoi(row[0]);

    mysql_free_result(res);
    mysql_close(conn);

    return exists;
}

int main() {
    const char *hostname = "localhost";
    const char *username = "root"; // Replace with your MySQL username
    const char *password = "password"; // Replace with your MySQL password
    const char *database_name = "your_database_name"; // Replace with your database name
    const char *table_name = "users"; // Replace with your table name
    const char *column_name = "username"; // Replace with the column name for usernames
    const char *user_to_check = "example_user"; // Replace with the username to check

    int exists = does_username_exist(hostname, username, password, database_name, table_name, column_name, user_to_check);
    
    if (exists) {
        printf("Username %s exists.\n", user_to_check);
    } else {
        printf("Username %s does not exist.\n", user_to_check);
    }

    return 0;
}