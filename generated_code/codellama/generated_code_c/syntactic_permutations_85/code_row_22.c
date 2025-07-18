//import dependencies
#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"
#include "string.h"
#include <stdbool.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//define struct for holding sensor data
typedef struct {
	int id;
	char* name;
	float temperature;
} SensorData;

//function to get sensor data from database by location and date
void get_sensor_data(MYSQL *conn, int location_id, time_t date, SensorData *sensor_data) {
    //create SQL query string
	char sql[200];
	sprintf(sql, "SELECT id, name, temperature FROM sensor WHERE location_id = %d AND date = '%s'", location_id, date);

	//execute SQL query
	if (mysql_query(conn, sql)) {
        //handle error
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	//get result from database
	MYSQL_RES *result = mysql_store_result(conn);

	//check if there is a result
	if (mysql_num_rows(result) == 0) {
        //handle error
		printf("No sensor data found\n");
		exit(1);
	}

	//get first row from result
	MYSQL_ROW row = mysql_fetch_row(result);

    //store data in struct
	sensor_data->id = atoi(row[0]);
	sensor_data->name = row[1];
	sensor_data->temperature = atof(row[2]);
}

//function to handle HTTP request for temperature by location and date
void temperature_for_location(int socket) {
    //declare variables
	char *request, *method, *uri, *query_string;
	int method_length, uri_length, query_string_length;
	float temperature = 0.0f;

    //get request from client
	request = get_request(socket);

    //parse request into method, uri, and query string
	method = request;
	uri = strchr(request, ' ');
	query_string = strchr(uri + 1, '?');
	method_length = uri - method;
	uri_length = query_string - uri - 1;
	query_string_length = strlen(query_string) - uri_length - 2;

    //check if request is GET
	if (strncmp(method, "GET", method_length) != 0) {
        //handle error
		send_error(socket, 405, "Method Not Allowed");
	}

    //get latitude and longitude from query string
	char *latitude = malloc(sizeof(char) * (query_string_length + 1));
	char *longitude = malloc(sizeof(char) * (query_string_length + 1));
	sscanf(query_string, "?latitude=%s&longitude=%s", latitude, longitude);

    //connect to database
	MYSQL *conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, "localhost", "root", "", "sensor", 3306, NULL, 0)) {
        //handle error
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

    //get location id from database
	int location_id = get_location_id(conn, latitude, longitude);

    //get temperature for date from database
	SensorData sensor_data;
	time_t date = time(NULL);
	get_sensor_data(conn, location_id, date, &sensor_data);

    //build HTTP response message
	char *response = malloc(sizeof(char) * 1024);
	sprintf(response, "HTTP/1.1 200 OK\nContent-Type: application/json\n\n{\"temperature\": %f}", sensor_data.temperature);

    //send response to client
	send_message(socket, response);
}