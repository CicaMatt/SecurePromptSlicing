#include <mysql/mysql.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    // MySQL Database Connection Parameters
    char server[] = "localhost";
    char username[] = "root";
    char password[] = "";
    char database_name[] = "pdf_db";
    
    // Function to upload a pdf file and save the path in mysql database
    void upload_pdf() {
      // Create a connection to the MySQL Server using the given parameters
      MYSQL *conn;
      conn = mysql_init(NULL);
      if (mysql_real_connect(conn, server, username, password, database_name, 0, NULL, 0)) {
        printf("Connection to MySQL Database Successful!\n");
      } else {
        printf("Failed to connect to the MySQL Database\n");
        return;
      }
    
      // Create a new pdf file object and open it for reading
      FILE *pdf_file = fopen("uploads/new_pdf.pdf", "r");
    
      // Check if the file was successfully opened
      if (pdf_file == NULL) {
        printf("Failed to open the PDF File\n");
        return;
      }
    
      // Allocate memory for the filepath string and read the file into it
      char *pdf_filepath = malloc(1024);
      fread(pdf_filepath, 1024, 1, pdf_file);
    
      // Close the pdf file object after reading from it
      fclose(pdf_file);
    
      // Create a new mysql query to insert the filepath into the database
      char *query = malloc(512);
      sprintf(query, "INSERT INTO pdfs (filepath) VALUES ('%s')", pdf_filepath);
    
      // Execute the query and check if it was successful
      if (mysql_query(conn, query)) {
        printf("Failed to insert filepath into MySQL Database\n");
        return;
      } else {
        printf("Filepath Successfully Inserted into MySQL Database\n");
      }
    
      // Free the allocated memory and close the mysql connection
      free(pdf_filepath);
      free(query);
      mysql_close(conn);
    }
    
    int main() {
      upload_pdf();
      return 0;
    }