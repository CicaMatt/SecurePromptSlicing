#include <stdlib.h>  // for exit() and EXIT_FAILURE
#include <mysql/mysql.h> // for mysql stuff
#include <string.h> // for strcpy, strcat, etc.

void upload_pdf(char *filepath) {
    char sql[256];
    
    // Connect to database
    MYSQL *conn;
    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "username",
                            "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }    
    
    // Prepare SQL query
    strcpy(sql, "INSERT INTO pdf_table (filepath) VALUES ('");
    strcat(sql, filepath);
    strcat(sql, "');");
    
    // Execute SQL query
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    
    // Close database connection
    mysql_close(conn);
}