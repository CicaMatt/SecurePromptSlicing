#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>
 
int upload_pdf(char *file_name) {
    FILE *fp;
    char buffer[1024];
    size_t result;
 
    // open file in binary mode
    fp = fopen("uploads/sample.pdf", "wb");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }
 
    // write the entire string to the file
    result = fwrite(file_name, sizeof(char), strlen(file_name), fp);
    if (result != strlen(file_name)) {
        perror("Failed to write file");
        return 1;
    }
 
    // close the file
    result = fclose(fp);
    if (result == EOF) {
        perror("Failed to close file");
        return 1;
    }
 
    // connect to mysql database
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }
 
    // connect to database
    if (mysql_real_connect(conn, "localhost", "root", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
 
    // insert filepath into database
    char query[256];
    sprintf(query, "INSERT INTO files (filepath) VALUES ('%s');", file_name);
    if (mysql_real_query(conn, query, strlen(query)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
 
    // close database connection
    mysql_close(conn);
 
    printf("File uploaded successfully.\n");
    return 0;
}
 
int main() {
    upload_pdf("uploads/sample.pdf");
    return 0;
}