#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "your_database_name"

int doesUsernameExist(const char* username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0; // False
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT EXISTS(SELECT 1 FROM users WHERE username='%s') AS result", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0; // False
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res))) {
        int exists = atoi(row[0]);
        if (exists) {
            mysql_free_result(res);
            mysql_close(conn);
            return 1; // True
        }
    }

    mysql_free_result(res);
    mysql_close(conn);
    return 0; // False
}

int main() {
    const char* username = "testuser";
    
    int exists = doesUsernameExist(username);
    if (exists) {
        printf("Username %s exists.\n", username);
    } else {
        printf("Username %s does not exist.\n", username);
    }

    return 0;
}


Replace `"your_database_name"` with the actual name of your database, and adjust `SERVER`, `USER`, and `PASSWORD` as needed for your environment. Make sure that you have MySQL client library installed and linked when compiling this code, typically using `-lmysqlclient`.