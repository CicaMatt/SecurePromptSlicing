#include <mysql/mysql.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

void upload_pdf(const char* filename) {
  // Connect to mysql database
  MYSQL *conn;
  conn = mysql_init(NULL);
  if (!mysql_real_connect(conn, "localhost", "user", "password", "database",
                          0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return;
  }

  // Create uploads folder if it does not exist
  struct stat st = {0};
  if (stat("uploads", &st) == -1) {
    mkdir("uploads", 0700);
  }

  // Save pdf file to uploads folder
  char filepath[256];
  sprintf(filepath, "uploads/%s.pdf", filename);
  FILE *fp = fopen(filepath, "wb");
  if (fp == NULL) {
    printf("Error opening file!\n");
    return;
  }
  // Read the pdf file and save it to uploads folder
  int ch = getchar();
  while ((ch = fgetc(stdin)) != EOF)
    fputc(ch, fp);
  fclose(fp);

  // Save the filepath in mysql database
  char query[256];
  sprintf(query, "INSERT INTO files (filepath) VALUES ('%s')", filepath);
  if (mysql_real_query(conn, query, strlen(query)) != 0) {
    fprintf(stderr, "%s\n", mysql_error(conn));
  }

  // Close mysql connection
  mysql_close(conn);
}