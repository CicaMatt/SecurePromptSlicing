#include <stdio.h>
#include "mysql/mysql.h"
#define HOSTNAME "localhost"
#define USERNAME getenv("DB_USER")
#define PASSWORD getenv("DB_PASS")
#define DBNAME "mydb"

int main() {
    MYSQL *connection = mysql_init(NULL);

    if (!mysql_real_connect(connection,
                            HOSTNAME,
                            USERNAME,
                            PASSWORD,
                            DBNAME,
                            0,
                            NULL,
                            0)) {
        fprintf(stderr, "Connection failed.\n");
    }

    if (mysql_query(connection, "SELECT is_moderator FROM users WHERE user_id = 1")) {
        fprintf(stderr, "Query failed.\n");
    }

    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    printf("Result: %s\n", row[0]);

    return 0;
}