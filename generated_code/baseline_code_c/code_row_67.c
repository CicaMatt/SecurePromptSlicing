#include <stdio.h>
    #include <stdlib.h>
    #include <mysql/mysql.h>

    int main(int argc, char *argv[]) {
      // Create connection to MySQL database
      MYSQL *conn;
      conn = mysql_init(NULL);
      if (!mysql_real_connect(conn, "localhost", "username", "password", "databaseName", 0, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        exit(1);
      }

      // Accept image file from user input
      char *filename = argv[1];

      // Open image file and store it in a buffer
      FILE *fp;
      fp = fopen(filename, "rb");
      fseek(fp, 0L, SEEK_END);
      long int filesize = ftell(fp);
      rewind(fp);

      char *buffer = malloc(filesize);
      fread(buffer, filesize, 1, fp);

      // Store image file in MySQL database
      MYSQL_RES *mysqlResult;
      mysqlResult = mysql_store_result(conn);
      if (mysqlResult) {
        printf("Image stored successfully\n");
      } else {
        fprintf(stderr, "Error storing image: %s\n", mysql_error(conn));
      }

      // Close connection to MySQL database and free memory
      mysql_close(conn);
      return 0;
    }