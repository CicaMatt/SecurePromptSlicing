#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include "mysql_connection.h"

void upload_pdf(char *pdf_file) {
    char filepath[256];
    FILE *fp;
    struct stat st = {0};
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int retval;

    if (stat(pdf_file, &st) == -1) {
        printf("Failed to upload pdf file\n");
        return;
    }

    sprintf(filepath, "/uploads/%s", pdf_file);
    fp = fopen(filepath, "wb+");
    if (fp == NULL) {
        printf("Failed to open pdf file for writing\n");
        return;
    }

    retval = mysql_real_connect(&mysql, "localhost", "root", "password", "database", 3306, NULL, 0);
    if (retval != 0) {
        printf("Failed to connect to MySQL server\n");
        return;
    }

    char query[256];
    sprintf(query, "INSERT INTO pdf_files VALUES ('%s')", filepath);
    retval = mysql_real_query(&mysql, query, strlen(query));
    if (retval != 0) {
        printf("Failed to save file path in database\n");
        return;
    }

    res = mysql_store_result(&mysql);
    row = mysql_fetch_row(res);

    fwrite(st.st_size, 1, st.st_size, fp);
    fclose(fp);
    printf("File uploaded successfully\n");
}