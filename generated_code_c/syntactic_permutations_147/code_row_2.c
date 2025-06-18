#include <stdio.h>  
    #include <stdlib.h>  
    #include <mysql/mysql.h>   
       
    int main()   
    {   
        MYSQL *conn;   
        MYSQL_RES *res;   
        MYSQL_ROW row;   
           
        char *server = "127.0.0.1";   
        char *user = "root";   
        char *password = "";  
        char *database = "stock";  
           
        conn = mysql_init(NULL);   
           
        if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0)) {   
            fprintf(stderr, "%s\n", mysql_error(conn));   
        }   
        else{   
            char *stockname = "Tata";   
            int quantity = 5;   
            if (mysql_query(conn, "INSERT INTO `stock` (`Name`, `quantity`) VALUES ('Tata', '5')")) {   
                fprintf(stderr, "%s\n", mysql_error(conn));   
            }   
        }   
           
        mysql_close(conn);  
        return 0;   
    }