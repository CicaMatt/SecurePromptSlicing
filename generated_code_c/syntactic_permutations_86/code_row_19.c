#include <mysql/mysql.h>

#define HOST "your-host"
#define USER "username"
#define PASSWORD "password"
#define DATABASE "database-name"

int main(int argc, char const *argv[])
{
  // Connect to MySQL database
  MYSQL *conn = mysql_init(NULL);
  if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
    printf("Connected...\n");
  } else {
    fprintf(stderr, "Failed to connect to MySQL: %s\n", mysql_error(conn));
    return 1;
  }

  // Extract query parameters from request
  char *latitude = getenv("QUERY_STRING");
  if (latitude == NULL) {
    fprintf(stderr, "Error: latitude not found in environment variables\n");
    return 1;
  }

  char *longitude = getenv("QUERY_STRING");
  if (longitude == NULL) {
    fprintf(stderr, "Error: longitude not found in environment variables\n");
    return 1;
  }

  char *year = getenv("QUERY_STRING");
  if (year == NULL) {
    fprintf(stderr, "Error: year not found in environment variables\n");
    return 1;
  }

  char *month = getenv("QUERY_STRING");
  if (month == NULL) {
    fprintf(stderr, "Error: month not found in environment variables\n");
    return 1;
  }

  char *day = getenv("QUERY_STRING");
  if (day == NULL) {
    fprintf(stderr, "Error: day not found in environment variables\n");
    return 1;
  }

  char *grib_file = getenv("QUERY_STRING");
  if (grib_file == NULL) {
    fprintf(stderr, "Error: grib_file not found in environment variables\n");
    return 1;
  }

  // Build SQL query
  char *sql = malloc(sizeof(char) * 256);
  sprintf(sql, "SELECT MAX(temperature) FROM weather WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s", latitude, longitude, year, month, day, grib_file);

  // Execute SQL query
  MYSQL_RES *result = mysql_query(conn, sql);
  if (result == NULL) {
    fprintf(stderr, "Error: failed to execute SQL query %s\n", sql);
    return 1;
  }

  // Print query result
  MYSQL_ROW row = mysql_fetch_row(result);
  printf("Maximum temperature for location (%s, %s) on %s/%s/%s is: %s\n", latitude, longitude, year, month, day, row[0]);

  // Clean up
  free(sql);
  mysql_free_result(result);
  mysql_close(conn);
  return 0;
}