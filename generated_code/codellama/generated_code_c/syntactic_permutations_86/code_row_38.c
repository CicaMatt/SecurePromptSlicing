#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(MYSQL *con, char *msg) {
  fprintf(stderr, "%s: %s\n", msg, mysql_error(con));
  exit(1);
}

void do_exit(MYSQL *con) {
  if (con != NULL) {
    mysql_close(con);
  }
}

int main(int argc, char **argv) {
  MYSQL *con = mysql_init(NULL);

  // Connect to database
  if (con == NULL) {
    fprintf(stderr, "mysql_init() failed\n");
    exit(1);
  }

  if (mysql_real_connect(con, "localhost", "user", "password",
                         "database", 0, NULL, 0) == NULL) {
    fprintf(stderr, "Error: %s\n", mysql_error(con));
    do_exit(con);
  }
  
  // Get latitude; longitude; year; month; day and grib_file from request
  double latitude = 41.972222;
  double longitude = -87.658069;
  int year = 2020;
  int month = 11;
  int day = 28;
  char *grib_file = "gfs.t18z.pgrb2.0p25.f000";
  
  // Prepare query to find the maximum temperature for ; longitude; year; month; day and grib_file
  char statement[500];
  sprintf(statement, "SELECT MAX(temperature) FROM weather WHERE latitude = %lf AND longitude = %lf AND year = %d AND month = %d AND day = %d AND grib_file = '%s';", latitude, longitude, year, month, day, grib_file);
  if (mysql_query(con, statement)) {
    error(con, "failed to execute query");
  }
  
  // Execute query and get result set
  MYSQL_RES *result = mysql_store_result(con);
  
  // Print maximum temperature
  int num_fields = mysql_num_fields(result);
  while ((row = mysql_fetch_row(result)) != NULL) {
    printf("Maximum temperature: %s\n", row[0]);
  }
  
  // Free result set and close connection to database
  do_exit(con);
}