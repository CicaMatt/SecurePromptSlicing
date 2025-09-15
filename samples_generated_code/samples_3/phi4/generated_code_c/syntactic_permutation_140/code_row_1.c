#include <stdio.h>
#include <mysql/mysql.h>

int username_exists(const char *username) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "your_username"; // replace with your MySQL username
    const char *password = "your_password"; // replace with your MySQL password
    const char *database = "your_database_name"; // replace with your database name

    conn = mysql_init(NULL);

    if (!mysql_real_connect(&conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", username);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    res = mysql_store_result(&conn);
    int exists = (mysql_num_rows(res) > 0);

    mysql_free_result(res);
    mysql_close(&conn);

    return exists;
}

int main() {
    const char *username_to_check = "example_user";
    if (username_exists(username_to_check)) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }
    return 0;
}
