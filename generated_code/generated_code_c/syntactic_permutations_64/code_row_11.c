// imports
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>
#include <sys/stat.h>
#include "m_pdf.h"

// function to upload pdf file and save the filepath in mysql database
void upload_pdf() {
    // create mysql connection object
    MYSQL *conn = mysql_init(NULL);
    
    // connect to mysql server with username, password, hostname, port number, socket file path and default database name
    if (!mysql_real_connect(conn, "localhost", "root", "password", "mydatabase", 3306, "/var/run/mysqld/mysqld.sock", 0)) {
        printf("Error connecting to mysql server\n");
        exit(1);
    }
    
    // query string to insert filepath of pdf file into mysql table
    char query[256];
    sprintf(query, "INSERT INTO files (filepath) VALUES ('%s')", "/home/user/Documents/pdf_files");
    
    // execute the query
    if (mysql_query(conn, query)) {
        printf("Error inserting filepath into mysql table\n");
        exit(1);
    }
    
    // fetch the last inserted id from mysql table
    char query2[256];
    sprintf(query2, "SELECT LAST_INSERT_ID() FROM files");
    
    // execute the query
    if (mysql_query(conn, query2)) {
        printf("Error fetching last inserted id from mysql table\n");
        exit(1);
    }
    
    // save the filepath of pdf file in a variable
    MYSQL_RES *result = mysql_store_result(conn);
    char *filepath;
    while ((row = mysql_fetch_row(result)) != NULL) {
        filepath = row[0];
    }
    
    // create pdf object with the filepath of pdf file
    PDF *pdf = m_new_pdf(filepath);
    
    // open the pdf file for reading
    if (m_open_pdf(pdf, M_OPEN_READ)) {
        printf("Error opening pdf file\n");
        exit(1);
    }
    
    // read the contents of pdf file and save it in a buffer
    size_t buflen = 4096;
    char *buf = malloc(buflen);
    if (m_read_pdf(pdf, buf, buflen)) {
        printf("Error reading pdf file\n");
        exit(1);
    }
    
    // close the pdf file
    m_close_pdf(pdf);
    
    // free the memory allocated for pdf object
    m_free_pdf(pdf);
    
    // free the memory allocated for buffer
    free(buf);
}