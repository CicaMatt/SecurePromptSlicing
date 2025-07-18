#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;

  char *server = "localhost";
  char *user = "root";
  char *password = "your_password";
  char *database = "temperatures";

  conn = mysql_init(NULL);

  if (!mysql_real_connect(conn, server, user, password, database,
                          0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  char *query = "SELECT MAX(temperature) FROM temperatures WHERE latitude=? AND longitude=? AND grib_file=? AND year=? AND month=? AND day=?";

  MYSQL_STMT *stmt = mysql_stmt_init(conn);
  if (mysql_stmt_prepare(stmt, query, strlen(query))) {
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(1);
  }

  float latitude = 40.7589;
  float longitude = -73.9851;
  unsigned short year = 2020;
  unsigned char month = 8;
  unsigned char day = 1;
  char grib_file[20] = "000";

  MYSQL_BIND bind[6];
  memset(bind, 0, sizeof(bind));

  bind[0].buffer_type = MYSQL_TYPE_FLOAT;
  bind[0].buffer = (char *)&latitude;
  bind[1].buffer_type = MYSQL_TYPE_FLOAT;
  bind[1].buffer = (char *)&longitude;
  bind[2].buffer_type = MYSQL_TYPE_STRING;
  bind[2].buffer = grib_file;
  bind[2].buffer_length = strlen(grib_file);
  bind[3].buffer_type = MYSQL_TYPE_SHORT;
  bind[3].buffer = (char *)&year;
  bind[4].buffer_type = MYSQL_TYPE_TINY;
  bind[4].buffer = (char *)&month;
  bind[5].buffer_type = MYSQL_TYPE_TINY;
  bind[5].buffer = (char *)&day;

  if (mysql_stmt_bind_param(stmt, bind)) {
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(1);
  }

  if (mysql_stmt_execute(stmt)) {
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(1);
  }

  res = mysql_use_result(conn);

  while ((row = mysql_fetch_row(res))) {
    printf("%s\n", row[0]);
  }

  mysql_free_result(res);
  mysql_stmt_close(stmt);
  mysql_close(conn);

  return 0;
}