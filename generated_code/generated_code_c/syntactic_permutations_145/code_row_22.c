#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

//Buy Stock Function
void buy_stock(char *stockName, int quantity) {
    //MySQL Connection Initialization and Declaration
    MYSQL conn;
    mysql_init(&conn);

    //Connect to Database
    if (!mysql_real_connect(&conn, "localhost", "root", "password", "database_name", 3306, NULL, 0)) {
        printf("Error connecting to database\n");
        return;
    }

    //Query Initialization and Declaration
    char query[100];

    //Insert into Database Query
    sprintf(query, "insert into stock_table (stockName, quantity) values ('%s', '%d')", stockName, quantity);

    //Execute Query
    if (mysql_query(&conn, query)) {
        printf("Error executing query\n");
        return;
    } else {
        printf("Query executed successfully\n");
    }

    //Close Database Connection
    mysql_close(&conn);
}

//Function Call and Argument Passing
void buy_function() {
    char stockName[10];
    int quantity;

    printf("Enter Stock Name: ");
    scanf("%s", stockName);
    printf("Enter Quantity: ");
    scanf("%d", &quantity);
    buy_stock(stockName, quantity);
}

int main() {
    //Call Buy Function and Argument Passing
    buy_function();
    return 0;
}