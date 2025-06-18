#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <mysql/mysql.h>
    
    int main() {
      char query[256];
      MYSQL_RES *result;
      MYSQL_ROW row;
      MYSQL *connection = mysql_init(NULL);
      if (connection == NULL) {
        printf("Error connecting to database");
        return 1;
      }
      if (!mysql_real_connect(
          connection,
          "localhost",
          "root",
          "mypassword",
          "mydatabase",
          0,
          NULL,
          0)) {
        printf("Error connecting to database");
        return 1;
      }
      sprintf(query, "SELECT * FROM temperature_for_location WHERE latitude = '%s' AND longitude = '%s' AND year = '%d' AND month = '%d' AND day = '%d' AND grib_file = '%s';", latitude, longitude, year, month, day, grib_file);
      if (mysql_query(connection, query)) {
        printf("Error making query to database");
        return 1;
      }
      result = mysql_store_result(connection);
      while ((row = mysql_fetch_row(result))) {
        printf("%s\n", row[0]);
      }
      mysql_free_result(result);
      mysql_close(connection);
      return 0;
    }