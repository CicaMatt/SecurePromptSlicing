#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

int main()
{
    char *username, password[50];
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    if (mysql_real_connect(con,
            "localhost",
            "root",
            "password",
            "database",
            0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        return -2;
    }

    char query[512];
    sprintf(query, "INSERT INTO `user` (`username`, `password`) VALUES ('%s', '%s')", username, password);

    if (mysql_query(con, query))
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        return -3;
    }

    printf("Data inserted successfully\n");

    mysql_close(con);

    return 0;
}