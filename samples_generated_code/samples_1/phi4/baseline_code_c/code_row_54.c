#include <mysql/mysql.h>
#include <stdio.h>

int check_username_exists(const char *username) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_init(&conn);
    
    if (!mysql_real_connect(&conn, "localhost", "root", "", "your_database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username='%s'", username);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    res = mysql_use_result(&conn);
    
    if ((row = mysql_fetch_row(res))) {
        int count = atoi(row[0]);
        mysql_free_result(res);
        mysql_close(&conn);
        return count > 0;
    }
    
    mysql_free_result(res);
    mysql_close(&conn);
    return 0;
}

int main() {
    const char *username = "example_user";
    if (check_username_exists(username)) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }
    return 0;
}