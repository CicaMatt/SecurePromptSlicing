#include <stdio.h> 
#include <string.h> 
#include <mysql/mysql.h> 

int upload_pdf(const char *filepath) { 
    MYSQL *conn; 
    MYSQL_RES *res; 
    MYSQL_ROW row; 
    char *server = "localhost"; 
    char *user = "root"; 
    char *password = "passw0rd"; 
    char *database = "pdf_db"; 
    conn = mysql_init(NULL); 

    if (!mysql_real_connect(conn, server, user, password, database, 3306, NULL, 0)) { 
        fprintf(stderr, "%s\n", mysql_error(conn)); 
        return EXIT_FAILURE; 
    } 

    char query[1024]; 
    sprintf(query, "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath); 

    if (mysql_query(conn, query)) { 
        fprintf(stderr, "%s\n", mysql_error(conn)); 
        return EXIT_FAILURE; 
    } 

    res = mysql_use_result(conn); 
    row = mysql_fetch_row(res); 

    if (row) { 
        printf("%s\n", row[0]); 
    } 

    mysql_free_result(res); 
    mysql_close(conn); 

    return EXIT_SUCCESS; 
}