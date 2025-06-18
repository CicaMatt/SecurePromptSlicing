#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

void upload_pdf(char* pdf_name, char* filepath) {
    // Save the uploaded PDF to uploads folder.
    FILE *fptr = fopen(filepath, "wb");
    fwrite(pdf_name, 1, strlen(pdf_name), fptr);
    fclose(fptr);
    
    // Update MySQL database with filepath.
    MYSQL* mysql_conn;
    mysql_conn = mysql_init(NULL);
    char db_host[]="localhost";
    char db_user[]="root";
    char db_passwd[]="password";
    char db_name[]="mydatabase";
    if (mysql_real_connect(mysql_conn, db_host, db_user, db_passwd, db_name, 0, NULL, 0)) {
        const char* sql = "UPDATE pdfs SET filepath='%s' WHERE id=1;";
        char query[256];
        sprintf(query, sql, filepath);
        mysql_real_query(mysql_conn, query, strlen(query));
    } else {
        printf("Failed to connect to database: %s\n", mysql_error(mysql_conn));
    }
}