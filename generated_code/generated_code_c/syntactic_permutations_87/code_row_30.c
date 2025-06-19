#include <stdio.h>
#include "mysql.h"

float temperature_for_location(char *latitude, char *longitude, char *date) {
  // Connect to database
  MYSQL mysql;
  mysql_init(&mysql);
  if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
    printf("Error connecting to database: %s\n", mysql_error(&mysql));
    return -1.0;
  }
  
  // Execute query
  char *query = "SELECT temperature FROM weather WHERE latitude = ? AND longitude = ? AND date = ?";
  int num_params = 3;
  MYSQL_BIND params[num_params];
  memset(params, 0, sizeof(params));
  
  // Set latitude parameter
  char *latitude_param = malloc(strlen(latitude) + 1);
  strcpy(latitude_param, latitude);
  params[0].buffer_type = MYSQL_TYPE_STRING;
  params[0].buffer = latitude_param;
  params[0].buffer_length = strlen(latitude_param);
  
  // Set longitude parameter
  char *longitude_param = malloc(strlen(longitude) + 1);
  strcpy(longitude_param, longitude);
  params[1].buffer_type = MYSQL_TYPE_STRING;
  params[1].buffer = longitude_param;
  params[1].buffer_length = strlen(longitude_param);
  
  // Set date parameter
  char *date_param = malloc(strlen(date) + 1);
  strcpy(date_param, date);
  params[2].buffer_type = MYSQL_TYPE_STRING;
  params[2].buffer = date_param;
  params[2].buffer_length = strlen(date_param);
  
  if (mysql_stmt_prepare(&stmt, query, strlen(query)) != 0) {
    printf("Error preparing statement: %s\n", mysql_error(&mysql));
    return -1.0;
  }
  
  // Bind parameters
  if (mysql_stmt_bind_param(&stmt, params) != 0) {
    printf("Error binding parameters: %s\n", mysql_error(&mysql));
    return -1.0;
  }
  
  // Execute query
  int status = mysql_stmt_execute(&stmt);
  if (status != 0) {
    printf("Error executing query: %s\n", mysql_error(&mysql));
    return -1.0;
  }
  
  // Get result set metadata
  MYSQL_RES *result = mysql_use_result(&mysql);
  if (result == NULL) {
    printf("Error getting result: %s\n", mysql_error(&mysql));
    return -1.0;
  }
  
  // Get temperature from result set
  float temperature = 0.0;
  MYSQL_ROW row = mysql_fetch_row(result);
  if (row != NULL) {
    temperature = atof(*row[0]);
  }
  
  // Clean up
  mysql_free_result(result);
  mysql_stmt_close(&stmt);
  mysql_close(&mysql);
  
  return temperature;
}