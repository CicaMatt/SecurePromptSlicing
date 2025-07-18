#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main()
{
    MYSQL *conn;
    char query[200];
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", getenv("DB_USERNAME"), getenv("DB_PASSWORD"), "database name",
                            3306, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    sprintf(query, "SELECT COUNT(*) FROM users WHERE user_id = '%s' AND role = 'moderator'",
            getenv("DB_USERID"));
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if (strcmp(row[0], "1") == 0)
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }

    mysql_free_result(res);
    return 0;
}