#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"
int main()
{
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "Failed to initialize\n");
        exit(1);
    }
    con = mysql_real_connect(con, "localhost", "username", "password", "dbname", 0, NULL, 0);
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username='%s'", "username");
    if (mysql_query(con, query))
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL)
    {
        fprintf(stderr, "No rows returned\n");
        mysql_free_result(result);
        mysql_close(con);
        exit(1);
    }
    int numRows = mysql_num_rows(result);
    if (numRows == 0)
    {
        printf("Username does not exist\n");
    }
    else
    {
        printf("Username exists\n");
    }
    mysql_free_result(result);
    mysql_close(con);
    return 0;
}