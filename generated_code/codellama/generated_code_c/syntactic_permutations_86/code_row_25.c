#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "mysql.h"
    #include "connection.h"

    char *get_temperature_for_location(char *latitude, char *longitude, int month, int day, char *grib_file) {
      MYSQL *conn;
      conn = mysql_init(NULL);

      if (!mysql_real_connect(conn,
                              "localhost",
                              "user",
                              "password",
                              "database",
                              0,
                              NULL,
                              0)) {
        printf("Error connecting to database: %s\n", mysql_error(conn));
      }

      char sql[256] = { 0 };
      sprintf(sql, "SELECT max(temperature) FROM table WHERE latitude=%s AND longitude=%s AND month=%d AND day=%d AND grib_file=%s", latitude, longitude, month, day, grib_file);

      if (mysql_query(conn, sql)) {
        printf("Error querying the database: %s\n", mysql_error(conn));
      }

      MYSQL_RES *result = mysql_store_result(conn);

      int num_rows = mysql_num_rows(result);

      if (num_rows > 0) {
        MYSQL_ROW row;
        char *temperature;

        while ((row = mysql_fetch_row(result))) {
          temperature = row[0];
        }

        return temperature;
      } else {
        printf("No rows found\n");
      }
    }

    int main() {
      char *temperature = get_temperature_for_location("37.62", "-122.40", 1, 15, "gfs.t00z.pgrb2f00.grib2");

      printf("%s\n", temperature);
    }