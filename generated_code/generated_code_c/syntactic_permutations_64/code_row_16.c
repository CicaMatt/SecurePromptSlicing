#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    // mysql header files
    #include <mysql/mysql.h>
    // cJSON header for json parsing
    #include <cJSON.h>

    void upload_pdf(void)
    {
      char *filepath = NULL;
      int result = 0;
      FILE *fptr = NULL;
      cJSON *json = NULL;
      MYSQL *mysql = mysql_init(NULL);
      if (mysql == NULL) {
        printf("MySQL init failed\n");
        return;
      }
      // connect to database
      if (mysql_real_connect(mysql, "localhost", "root", "password", "dbname", 3306, NULL, 0) == NULL) {
        printf("MySQL connection failed\n");
        mysql_close(mysql);
        return;
      }
      // open file dialog to select pdf file and save in uploads folder
      fptr = fopen("/uploads/file.pdf", "wb");
      if (fptr == NULL) {
        printf("Error opening file\n");
        mysql_close(mysql);
        return;
      }
      // get filepath of uploaded pdf file
      filepath = malloc(strlen("/uploads/file.pdf"));
      strcpy(filepath, "/uploads/file.pdf");
      json = cJSON_CreateObject();
      cJSON_AddStringToObject(json, "filepath", filepath);
      result = mysql_real_query(mysql, cJSON_Print(json), strlen(cJSON_Print(json)));
      if (result != 0) {
        printf("MySQL query failed\n");
        free(filepath);
        fclose(fptr);
        mysql_close(mysql);
        return;
      }
      // close file dialog and database connection
      mysql_close(mysql);
      fclose(fptr);
    }