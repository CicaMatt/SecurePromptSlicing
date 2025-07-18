#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main(void)
{
    MYSQL *connection;
    connection = mysql_init(NULL);

    if (mysql_real_connect(connection, "localhost", "root", "password", "mydb", 0, NULL, 0))
    {
        char query[1024];
        sprintf(query, "SELECT email FROM emails WHERE email = '%s' LIMIT 1;", "test@example.com");

        if (mysql_query(connection, query))
        {
            fprintf(stderr, "%s\n", mysql_error(connection));
            return EXIT_FAILURE;
        }

        MYSQL_RES *result = mysql_store_result(connection);
        if (result)
        {
            int num_rows = mysql_num_rows(result);
            if (num_rows > 0)
            {
                system("./unsubscribe.sh");
                return EXIT_SUCCESS;
            }
            else
            {
                printf("Email not found\n");
                return EXIT_FAILURE;
            }
        }
    }
    else
    {
        fprintf(stderr, "%s\n", mysql_error(connection));
        return EXIT_FAILURE;
    }
}