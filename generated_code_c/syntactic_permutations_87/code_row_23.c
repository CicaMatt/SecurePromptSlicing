#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include "mysql/mysql.h"
    
    float temperature_for_location(float latitude, float longitude, char* date) {
      /* Connect to database */
      MYSQL *conn;
      conn = mysql_init(NULL);
      if (conn == NULL) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
      }
    
      if (mysql_real_connect(conn, "localhost", "root", "password", "temperatures", 0, NULL, 0) == NULL) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
      }
    
      /* Execute query */
      char sql[256];
      sprintf(sql, "SELECT temperature FROM temperatures WHERE latitude=%f AND longitude=%f AND date='%s'", latitude, longitude, date);
      
      if (mysql_query(conn, sql)) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
      }
    
      /* Get result */
      MYSQL_RES *res;
      res = mysql_store_result(conn);
      if (res == NULL) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
      }
    
      MYSQL_ROW row;
      row = mysql_fetch_row(res);
      if (row == NULL) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
      }
    
      /* Convert to float */
      char *end;
      char temp_str[256];
      strcpy(temp_str, row[0]);
      float temperature = strtof(temp_str, &end);
      
      /* Clean up */
      mysql_free_result(res);
      mysql_close(conn);
    
      return temperature;
    }