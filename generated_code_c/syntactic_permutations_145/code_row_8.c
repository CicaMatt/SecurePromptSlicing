#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    void buy_stock(char *name,int quantity){
        MYSQL *conn;
        conn=mysql_init(NULL);
    
        if(!mysql_real_connect(conn,"localhost","root","password","db",0,NULL,0)){
            fprintf(stderr, "Error : %s\n",mysql_error(conn));
            exit(1);
        }
    
        char query[255];
        sprintf(query,"INSERT INTO stock (name) VALUES ('%s')",name);
        if(mysql_real_query(conn,query,sizeof(query))){
            fprintf(stderr, "Error : %s\n",mysql_error(conn));
            exit(1);
        }
    
        mysql_close(conn);
    }
    
    void buy_function(char *name){
        // Your code here
    }