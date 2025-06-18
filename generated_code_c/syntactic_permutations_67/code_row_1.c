#include <mysql.h>
#include <stdio.h>
#include <string.h>

const char *host = "localhost";
const char *user = "root";
const char *pass = "";
const char *db = "image_storage";

int main(void) {
  // Connect to database
  MYSQL *conn;
  conn = mysql_init(NULL);
  if (!mysql_real_connect(
        conn,
        host,
        user,
        pass,
        db,
        0,
        NULL,
        0
      )) {
    printf("Connection failed\n");
    return 1;
  }

  // Create the table if it doesn't exist
  const char *create_query = "CREATE TABLE IF NOT EXISTS image (id INT AUTO_INCREMENT PRIMARY KEY, data LONGBLOB)";
  mysql_real_query(conn, create_query, strlen(create_query));

  // Insert the image file into the table
  FILE *image;
  image = fopen("path/to/file.jpg", "rb");
  if (!image) {
    printf("File not found\n");
    return 1;
  }
  fseek(image, 0, SEEK_END);
  long int size = ftell(image);
  rewind(image);
  char *blob = malloc(size);
  if (!blob) {
    printf("Memory allocation error\n");
    return 1;
  }
  fread(blob, size, 1, image);

  const char *insert_query = "INSERT INTO image (data) VALUES (?)";
  MYSQL_STMT *stmt = mysql_stmt_init(conn);
  if (!stmt) {
    printf("Statement error\n");
    return 1;
  }
  if (mysql_stmt_prepare(stmt, insert_query, strlen(insert_query))) {
    printf("Prepare error: %s\n", mysql_stmt_error(stmt));
    return 1;
  }
  MYSQL_BIND params[1];
  memset(params, 0, sizeof(params));

  ulong len = size;
  params[0].buffer_type = MYSQL_TYPE_LONG_BLOB;
  params[0].is_null = 0;
  params[0].length = &len;
  params[0].buffer = blob;

  if (mysql_stmt_bind_param(stmt, params)) {
    printf("Bind error: %s\n", mysql_stmt_error(stmt));
    return 1;
  }
  if (mysql_stmt_execute(stmt)) {
    printf("Execute error: %s\n", mysql_stmt_error(stmt));
    return 1;
  }
  free(blob);
  fclose(image);
  mysql_stmt_close(stmt);
  mysql_close(conn);
  return 0;
}