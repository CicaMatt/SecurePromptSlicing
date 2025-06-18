#include <stdio.h>
#include <mysql/mysql.h>

int main(void) {
  MYSQL* conn;
  MYSQL_RES* res;
  MYSQL_ROW row;

  char* server = "localhost";
  char* user = "root";
  char* password = "123456"; /* set me first */
  char* database = "weather";

  conn = mysql_init(NULL);

  /* Connect to database */
  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return 1;
  }

  /* Send SQL query */
  if (mysql_query(conn, "SELECT MAX(temp) FROM weather WHERE lat = ? AND lon = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return 1;
  }

  res = mysql_use_result(conn);

  /* Print results */
  printf("MySQL result:\n");
  while ((row = mysql_fetch_row(res))) {
    printf("%s\n", row[0]);
  }

  /* Clean up */
  mysql_free_result(res);
  mysql_close(conn);

  return 0;
}