#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "mysql_connection.h"

void upload_pdf(char *filepath) {
  MYSQL *conn;
  char query[512];
  int result;
  
  // Save the file in the uploads folder
  FILE *fp = fopen("uploads/filename", "wb");
  if (fp == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  
  // Get the filepath of the pdf file
  char filepath[256];
  sprintf(filepath, "/uploads/%s", filename);
  
  // Save the filepath in the mysql database
  conn = mysql_init(NULL);
  if (conn == NULL) {
    printf("Error initializing connection to MySQL!\n");
    exit(1);
  }
  if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
    printf("Error connecting to database: %s\n", mysql_error(conn));
    exit(1);
  }
  sprintf(query, "INSERT INTO pdf (filepath) VALUES ('%s')", filepath);
  result = mysql_query(conn, query);
  if (result != 0) {
    printf("Error saving filepath to database: %s\n", mysql_error(conn));
    exit(1);
  }
  
  // Download the pdf file
  FILE *pdf = fopen(filepath, "rb");
  if (pdf == NULL) {
    printf("Error opening pdf file!\n");
    exit(1);
  }
  char buffer[8192];
  int nread;
  while ((nread = fread(buffer, 1, sizeof(buffer), pdf)) > 0) {
    write(1, buffer, nread);
  }
  fclose(pdf);
  
  // Clean up
  mysql_close(conn);
  fclose(fp);
}