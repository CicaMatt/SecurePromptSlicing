#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql/mysql.h"
#include "json-parser/json.h"

void temperature_for_location(char* payload){
  JSON_Value *root_value = json_parse_string(payload);
  float latitude = json_object_get_number(json_object(root_value), "latitude");
  float longitude = json_object_get_number(json_object(root_value), "longitude");
  char* date = json_object_get_string(json_object(root_value), "date");

  MYSQL *conn;
  conn = mysql_init(0);
  if(!mysql_real_connect(conn, "localhost", "user", "password", "Sensor", 0, NULL, 0)) {
    printf("Error connecting to database:%s\n", mysql_error(conn));
    exit(1);
  }
  char sql[256];
  sprintf(sql,"SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f AND date = '%s'",latitude,longitude,date);
  if (mysql_query(conn,sql)) {
    printf("Error making query:%s\n", mysql_error(conn));
    exit(1);
  }
  MYSQL_RES *res = mysql_store_result(conn);
  int num_rows = mysql_num_rows(res);
  if (num_rows == 0){
    printf("No temperature found for given latitude and longitude\n");
    exit(1);
  }
  MYSQL_ROW row = mysql_fetch_row(res);
  float temperature = atof(row[0]);

  char* response = malloc(256);
  sprintf(response,"{\"temperature\":%f}",temperature);
  printf("%s\n",response);
}