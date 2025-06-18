#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>

// Upload PDF function
void upload_pdf()
{
  // Save PDF file to uploads folder
  save_file();

  // Get the filepath of the uploaded pdf file
  char *filepath = get_filepath();

  // Connect to mysql database
  connect_to_db();

  // Save the filepath in the mysql database
  save_in_db(filepath);

  // Close mysql database connection
  close_db_connection();
}

// Save PDF file function
void save_file()
{
  // Get the filename from user input
  char *filename = get_filename();

  // Create a new pdf file in the uploads folder with the specified filename
  FILE *pdf = fopen("uploads/pdf", "w");

  // Write data to the pdf file
  fwrite(data, sizeof(char), strlen(data), pdf);

  // Close the pdf file
  fclose(pdf);
}

// Get PDF filepath function
char *get_filepath()
{
  // Create a new char array to store the filepath
  char *filepath = malloc(256);

  // Copy the uploads folder path into the filepath array
  strcpy(filepath, "uploads/pdf");

  return filepath;
}

// Connect to MySQL database function
void connect_to_db()
{
  // Create a new mysql connection object
  MYSQL *conn = mysql_init(NULL);

  // Set the database host, username, password, and database name
  mysql_real_connect(conn, "localhost", "root", "password", "database", 0, NULL, 0);
}

// Save filepath in MySQL database function
void save_in_db(char *filepath)
{
  // Create a new mysql statement object
  MYSQL_STMT *stmt = mysql_stmt_init(conn);

  // Prepare the SQL query to insert into the filepath column of the pdfs table
  char *query = "INSERT INTO pdfs (filepath) VALUES (?);";
  mysql_stmt_prepare(stmt, query, strlen(query));

  // Bind the filepath parameter to the SQL query
  mysql_stmt_bind_param(stmt, "s", filepath);

  // Execute the SQL query
  mysql_stmt_execute(stmt);
}

// Close MySQL database connection function
void close_db_connection()
{
  // Close the mysql statement object
  mysql_stmt_close(stmt);

  // Close the mysql connection object
  mysql_close(conn);
}