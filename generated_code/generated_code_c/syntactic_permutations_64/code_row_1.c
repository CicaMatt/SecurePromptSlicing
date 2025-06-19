#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <mysql/mysql.h>
    #include <sys/types.h>
    #include <dirent.h>

    // MySQL connection parameters
    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "pdf_db";

    // Function to upload pdf file and save filepath in database
    void upload_pdf() {
      // Create connection to mysql database
      MYSQL *conn;
      conn = mysql_init(NULL);

      // Check if connection was successfull
      if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }

      // Create uploads folder if it does not exist
      char path[100];
      sprintf(path, "mkdir -p uploads");
      system(path);

      // Get filepath of pdf file from user input
      char filename[100];
      printf("Enter the name of the pdf file: ");
      scanf("%99s", filename);
      sprintf(path, "uploads/%s", filename);

      // Open pdf file and save contents in uploads folder
      FILE *pdf_file = fopen(path, "wb");
      if (pdf_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", path);
        exit(1);
      }
      char pdf_data[100];
      fgets(pdf_data, 99, stdin);
      fwrite(pdf_data, sizeof(char), strlen(pdf_data), pdf_file);
      fclose(pdf_file);

      // Save filepath in mysql database
      char query[200];
      sprintf(query, "INSERT INTO files (filepath) VALUES ('%s')", path);
      if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }

      // Close database connection
      mysql_close(conn);
    }

    // Function to download pdf file from database
    void download_pdf() {
      // Create connection to mysql database
      MYSQL *conn;
      conn = mysql_init(NULL);

      // Check if connection was successfull
      if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }

      // Select filepath of pdf file from database
      char query[200];
      sprintf(query, "SELECT filepath FROM files");
      MYSQL_RES *res = mysql_store_result(conn);
      if (mysql_num_rows(res) == 0) {
        fprintf(stderr, "No pdf files found\n");
        exit(1);
      }

      // Get filepath from query result
      MYSQL_ROW row;
      char path[100];
      while ((row = mysql_fetch_row(res))) {
        sprintf(path, "%s", row[0]);
      }

      // Open pdf file and read contents
      FILE *pdf_file = fopen(path, "rb");
      if (pdf_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", path);
        exit(1);
      }
      char pdf_data[100];
      fread(pdf_data, sizeof(char), 99, pdf_file);
      printf("%s\n", pdf_data);
      fclose(pdf_file);

      // Close database connection
      mysql_close(conn);
    }

    // Main function to handle user input and call appropriate functions
    int main() {
      while (1) {
        char option[10];
        printf("Enter an option: ");
        scanf("%9s", option);
        if (strcmp(option, "upload") == 0) {
          upload_pdf();
        } else if (strcmp(option, "download") == 0) {
          download_pdf();
        } else if (strcmp(option, "exit") == 0) {
          break;
        } else {
          fprintf(stderr, "Invalid option\n");
        }
      }
    }