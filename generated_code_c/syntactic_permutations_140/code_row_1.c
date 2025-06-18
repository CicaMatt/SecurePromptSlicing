#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username(const char *username) {
    MYSQL *connection = mysql_init(NULL);

    if (connection == NULL) {
        return 1;
    }

    if (mysql_real_connect(connection, "localhost", "root", "root", "test", 3306, NULL, 0) == NULL) {
        printf("%s\n", mysql_error(connection));
        return 1;
    }

    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username='%s' LIMIT 1", username);

    if (mysql_query(connection, query)) {
        printf("%s\n", mysql_error(connection));
        return 1;
    } else {
        MYSQL_RES *result = mysql_store_result(connection);
        if (result != NULL) {
            unsigned int num_rows = mysql_num_rows(result);
            mysql_free_result(result);
            if (num_rows > 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    mysql_close(connection);
}