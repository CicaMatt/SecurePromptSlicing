#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *hostname, const char *username, const char *password, const char *database_name, const char *user_to_check) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return 0;
    }

    if (!mysql_real_connect(&conn, hostname, username, password, database_name, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", user_to_check);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    res = mysql_store_result(&conn);

    if (res) {
        row = mysql_fetch_row(res);
        int count = atoi(row[0]);
        mysql_free_result(res);
        
        mysql_close(&conn);
        return count > 0 ? 1 : 0; // Returns true (1) if user exists, false (0) otherwise
    } else {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }
}

int main() {
    const char *hostname = "localhost";
    const char *username = "root";
    const char *password = "";
    const char *database_name = "your_database";
    const char *user_to_check = "test_user";

    int exists = check_username_exists(hostname, username, password, database_name, user_to_check);
    
    if (exists) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}


**Note:** Before running this code, ensure you have the MySQL development libraries installed and properly configured in your environment. Also, replace `your_database` with the actual name of your database and provide valid credentials for connecting to the database server.