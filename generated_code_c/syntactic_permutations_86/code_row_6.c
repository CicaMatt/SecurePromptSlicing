#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"

int main(void) {
  // Set up the HTTP server
  http_server *server = malloc(sizeof(http_server));
  if (http_server_init(server, 8080) != 0) {
    printf("Could not start server\n");
    return 1;
  }

  // Connect to the MySQL database
  MYSQL *db = mysql_init(NULL);
  if (db == NULL) {
    printf("Could not connect to MySQL database\n");
    http_server_free(server);
    return 1;
  }

  if (mysql_real_connect(db, "localhost", "root", "password", "weather", 3306, NULL, 0) == NULL) {
    printf("Could not connect to MySQL database\n");
    mysql_close(db);
    http_server_free(server);
    return 1;
  }

  // Define the endpoint and handler
  http_endpoint *endpoint = malloc(sizeof(http_endpoint));
  if (http_endpoint_init(endpoint, "/api/temperature_for_location", HTTP_GET, server) != 0) {
    printf("Could not create endpoint\n");
    mysql_close(db);
    http_server_free(server);
    return 1;
  }
  
  // Define the handler function
  endpoint->handler = ^(http_request *request, http_response *response) {
    printf("Received request for temperature\n");
    
    // Extract query parameters from the URL
    double latitude = strtod(request->query.latitude, NULL);
    double longitude = strtod(request->query.longitude, NULL);
    int year = atoi(request->query.year);
    int month = atoi(request->query.month);
    int day = atoi(request->query.day);
    char *grib_file = request->query.grib_file;
    
    // Define the query to execute on the database
    char *query = malloc(sizeof(char) * 1024);
    sprintf(query, "SELECT MAX(temperature) FROM weather WHERE latitude=%f AND longitude=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s'", latitude, longitude, year, month, day, grib_file);
    
    // Execute the query and get the result
    MYSQL_RES *result = mysql_query(db, query);
    if (result == NULL) {
      printf("Could not execute query\n");
      http_response_set_status(response, 500);
      http_response_write_body(response, "Internal Server Error", strlen("Internal Server Error"));
      return;
    }
    
    // Get the result from the database
    MYSQL_ROW row = mysql_fetch_row(result);
    double temperature = atof(row[0]);
    
    // Set the response body and headers
    char *body = malloc(sizeof(char) * 128);
    sprintf(body, "Temperature: %.2f", temperature);
    http_response_set_status(response, 200);
    http_response_write_body(response, body, strlen(body));
    
    // Clean up
    mysql_free_result(result);
    free(query);
    free(body);
  };
  
  // Run the server forever
  while (1) {
    http_server_run(server);
  }
  
  return 0;
}