#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "upload_pdf.h"

void upload_pdf(char *filename)
{
    char filepath[1024];
    FILE *fp;
    MYSQL_RES *result;
    MYSQL_ROW row;

    // Save the pdf file in the uploads folder
    sprintf(filepath, "./uploads/%s", filename);
    fp = fopen(filepath, "wb");
    if (fp == NULL)
    {
        printf("Error: failed to open file\n");
        return;
    }

    // Save the filepath in the mysql database
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "password",
                            "pdf_database", 3306,
                            NULL, 0))
    {
        printf("Error: failed to connect to database\n");
        return;
    }

    char query[1024];
    sprintf(query, "INSERT INTO pdf_files (filepath) VALUES ('%s');", filepath);
    if (mysql_query(conn, query))
    {
        printf("Error: failed to insert into database\n");
        return;
    }

    // Get the filepath from the mysql database and download the pdf file
    sprintf(query, "SELECT filepath FROM pdf_files WHERE id = %s;", filename);
    if (mysql_query(conn, query))
    {
        printf("Error: failed to select from database\n");
        return;
    }
    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    sprintf(filepath, "%s", row[0]);
    fp = fopen(filepath, "wb");
    if (fp == NULL)
    {
        printf("Error: failed to open file\n");
        return;
    }
}