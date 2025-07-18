#include <stdio.h> 
    #include <stdlib.h> 
    #include <mysql/mysql.h> 
    
    void insertData(char *stock_name, int quantity) { 
        MYSQL *conn; 
        MYSQL_RES *res; 
        MYSQL_ROW row; 
        
        char *server = "localhost"; 
        char *user = "root"; 
        char *password = "root"; 
        char *database = "stocks"; 
        
        conn = mysql_init(NULL); 
    
        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) { 
            printf("Error connecting to database.\n"); 
            exit(1); 
        } 
        
        char *sql = "INSERT INTO stock_view (stock_name, quantity) VALUES ('%s', %d)"; 
        if (mysql_query(conn, sql)) { 
            printf("Error inserting data into table.\n"); 
            exit(1); 
        } 
        
        mysql_close(conn); 
    }