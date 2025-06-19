#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main()
{
    char email_address[256];
    printf("Enter your email address: ");
    fgets(email_address, 256, stdin);
    unsubscribe(email_address);
    return 0;
}
void unsubscribe(char *email_address)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "12345678";
    char *database = "unsubscribes";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    sprintf(query, "SELECT * FROM subscribers WHERE email='%s'", email_address);
    mysql_real_query(conn, query, strlen(query));

    res = mysql_store_result(conn);

    if (mysql_num_rows(res) == 0)
    {
        printf("You are not subscribed to our newsletter\n");
    }
    else
    {
        sprintf(query, "DELETE FROM subscribers WHERE email='%s'", email_address);
        mysql_real_query(conn, query, strlen(query));
        printf("You have successfully unsubscribed from our newsletter\n");
    }
}