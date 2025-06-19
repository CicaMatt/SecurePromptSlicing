#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

//Function to connect to database
MYSQL* mysql_connect();

//Function to insert into the database
int buy_stock(char *name, int quantity);

//Function to buy stock
void buy_function(char *name);

//Main function
int main()
{
    char name[50];
    int quantity;

    //Get the stock name and quantity from the user
    printf("Enter the stock name: ");
    scanf("%s", &name);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    //Call buy_stock function to insert into database
    buy_stock(name, quantity);

    return 0;
}

//Function to connect to mysql database
MYSQL* mysql_connect()
{
    MYSQL *conn = NULL;
    conn = mysql_init(NULL);

    //Check if connection is established
    if (!mysql_real_connect(conn, "localhost", "root", "password",
                            "stock_exchange", 3306, NULL, 0))
    {
        printf("Error connecting to database\n");
        return NULL;
    }
    else
    {
        printf("Connected to database successfully\n");
        return conn;
    }
}

//Function to insert into the database
int buy_stock(char *name, int quantity)
{
    MYSQL *conn = mysql_connect();
    char query[1024] = {0};

    //Create SQL query string
    sprintf(query, "INSERT INTO stock (name, quantity) VALUES ('%s', %d)", name, quantity);

    //Execute the query
    if (mysql_query(conn, query))
    {
        printf("Error inserting into database\n");
        return 0;
    }
    else
    {
        printf("Data inserted successfully\n");
        mysql_close(conn);
        return 1;
    }
}

//Function to buy stock
void buy_function(char *name)
{
    MYSQL *conn = mysql_connect();
    char query[1024] = {0};

    //Create SQL query string
    sprintf(query, "SELECT quantity FROM stock WHERE name='%s'", name);

    //Execute the query
    if (mysql_query(conn, query))
    {
        printf("Error fetching data from database\n");
        mysql_close(conn);
        return;
    }
    else
    {
        MYSQL_RES *result = mysql_use_result(conn);
        int quantity = 0;

        //Fetch the data
        while (MYSQL_ROW row = mysql_fetch_row(result))
        {
            quantity = atoi(row[0]);
        }
        printf("Stock quantity is %d\n", quantity);

        //Update the quantity in the database
        sprintf(query, "UPDATE stock SET quantity=%d WHERE name='%s'", quantity + 1, name);
        if (mysql_query(conn, query))
        {
            printf("Error updating data in database\n");
            mysql_close(conn);
            return;
        }
    }
}