#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *host, const char *user, const char *password, const char *database, const char *username) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_init(&conn);

    if (!mysql_real_connect(&conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return 0; // false
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0; // false
    }

    res = mysql_use_result(&conn);

    row = mysql_fetch_row(res);
    int exists = atoi(row[0]) > 0;

    mysql_free_result(res);
    mysql_close(&conn);

    return exists;
}

int main() {
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "your_password"; // replace with your MySQL password
    const char *database = "your_database"; // replace with your database name
    const char *username_to_check = "test_user";

    int exists = check_username_exists(host, user, password, database, username_to_check);
    
    if (exists) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }
    
    return 0;
}


Note: Replace `"your_password"` and `"your_database"` with your actual MySQL credentials and database name. Additionally, ensure that the `mysqlclient` library is installed on your system for this code to compile and run successfully. You can typically install it via a package manager like `apt-get`, `yum`, or equivalent, depending on your operating system.