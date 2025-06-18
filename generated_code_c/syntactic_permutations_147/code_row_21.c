#include <stdio.h>
    #include <stdlib.h>
    #include <mysql/mysql.h>
    
    MYSQL* connection;
    char query[200];
    
    int main() {
        mysql_init(&connection);
        
        if (mysql_real_connect(&connection, "localhost", "root", "password", "stocks", 3306, NULL, 0)){
            printf("connected\n");
            
            // get stock name and quantity from form
            char stockName[255];
            int quantity;
            
            scanf("%s", &stockName);
            scanf("%d", &quantity);
            
            sprintf(query, "INSERT INTO orders (name, quantity) VALUES ('%s', %d)", stockName, quantity);
            mysql_query(&connection, query);
        }
        
        return 0;
    }