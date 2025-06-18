//Importing libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

//function for inserting data into database
int insert_data(char *stock_name, int stock_quantity, char *username) {
    //Declaring variables
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "123456789"; 
    char *database = "stock_database";
    char query[200] = {0};
    int qstate;
    
    //Creating connection to database
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, 
            database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    
    //Inserting data into database
    sprintf(query, "INSERT INTO buy_orders (stock_name, stock_quantity, username) VALUES ('%s', %d, '%s')", 
            stock_name, stock_quantity, username);
    qstate = mysql_query(conn, query);
    
    //Checking for errors in query execution
    if (qstate != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    
    //Closing connection to database
    mysql_close(conn);
    
    //Returning success
    return 0;
}