Here is the code for the above description:


#include <stdio.h>
#include<stdlib.h>
//including mysql libraries
#include "mysql.h"
#include <string.h>
int main()
{
   //creating a structure to store mysql connection parameters
    struct conn_info {
        char *host;
        int port;
        char *user;
        char *passwd;
        char *db;
    };
    
    //initializing the connection parameters
    struct conn_info info = {"localhost", 3306, "root", "root", "stocks"};
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *query = "INSERT INTO orders(stockname,quantity) VALUES('GOOG',12);";
    //establishing the connection with the database
    if (mysql_init(&mysql) == NULL)
        exit(1);
    
    mysql_real_connect(&mysql, info.host,info.user,info.passwd,info.db,0,NULL,0);
    //inserting data into the table
    if (mysql_query(&mysql, query)) {
        printf("Could not insert data\n");
        exit(1);
    }
    else{
        printf("\nData inserted successfully\n");
    }
}