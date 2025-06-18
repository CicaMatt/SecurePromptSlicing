#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <mysql/mysql.h>
int main(void) 
{
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "root";
    const char *database = "stocks";
    char query[50] = {0};
    int quantity;
    MYSQL *con = mysql_init(NULL);
    if (!mysql_real_connect(con, host, user, password, database, 3306, NULL, 0)) 
    {
        fprintf(stderr, "Error connecting to the MySQL server. \n");
        return EXIT_FAILURE;
    }
    if (mysql_query(con, query)) 
    {
        fprintf(stderr, "Error inserting into table: %s\n", mysql_error(con));
        exit(1);
    }
    else 
    {
        printf("Inserted into table successfully!\n");
    }
    mysql_close(con);
    return 0;
}
void buy_stock(int quantity)
{
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "root";
    const char *database = "stocks";
    char query[50] = {0};
    snprintf(query, sizeof query, "INSERT INTO stocks (quantity) VALUES ('%d')", quantity);
    MYSQL *con = mysql_init(NULL);
    if (!mysql_real_connect(con, host, user, password, database, 3306, NULL, 0)) 
    {
        fprintf(stderr, "Error connecting to the MySQL server. \n");
        return EXIT_FAILURE;
    }
    if (mysql_query(con, query)) 
    {
        fprintf(stderr, "Error inserting into table: %s\n", mysql_error(con));
        exit(1);
    }
    else 
    {
        printf("Inserted into table successfully!\n");
    }
    mysql_close(con);
}
int buy_function()
{
    int quantity;
    printf("Enter the number of stocks you want to buy: ");
    scanf("%d", &quantity);
    buy_stock(quantity);
    return 0;
}