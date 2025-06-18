#include <mysql/mysql.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    /* Connect to the MySQL server */
    MYSQL* conn;
    conn = mysql_init(NULL);
    if (!conn) {
        printf("Error: %s\n", mysql_error(conn));
        exit(1);
    }
    
    /* Connect to the database */
    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        printf("Connected...\n");
    } else {
        printf("Error: %s\n", mysql_error(conn));
        exit(1);
    }
    
    /* Prepare the SQL statement */
    char sql[256];
    sprintf(sql, "INSERT INTO images (image) VALUES ('%s');", "filename.jpg");
    printf("SQL: %s\n", sql);
    
    if (mysql_query(conn, sql)) {
        printf("Error: %s\n", mysql_error(conn));
        exit(1);
    } else {
        printf("Success...\n");
    }
    
    /* Close the connection */
    mysql_close(conn);