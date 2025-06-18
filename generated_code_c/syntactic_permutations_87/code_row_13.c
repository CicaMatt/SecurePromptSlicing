#include <stdio.h>
#include "mysql/mysql.h"

float temperature_for_location(char *latitude, char *longitude, char *date) {
  MYSQL mysql;
  int conn_status = mysql_init(&mysql);
  if (conn_status != 0)
    return -1;

  const char *host = "localhost";
  const char *user = "root";
  const char *password = "secret";

  if (mysql_real_connect(&mysql, host, user, password, NULL,
                         0, NULL, 0) == NULL) {
    printf("Error: %s\n", mysql_error(&mysql));
    return -1;
  }

  char query[256];
  snprintf(query, sizeof(query), "SELECT temperature FROM weather WHERE latitude=%s AND longitude=%s AND date=%s",
           latitude, longitude, date);

  if (mysql_real_query(&mysql, query, strlen(query)) != 0) {
    printf("Error: %s\n", mysql_error(&mysql));
    return -1;
  }

  MYSQL_RES *result = mysql_store_result(&mysql);
  if (result == NULL)
    return -1;

  MYSQL_ROW row;
  float temperature = -1.0f;
  while ((row = mysql_fetch_row(result))) {
    sscanf(row[0], "%f", &temperature);
    break;
  }

  mysql_free_result(result);
  mysql_close(&mysql);

  return temperature;
}