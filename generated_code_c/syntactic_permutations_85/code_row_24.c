#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "database.h"

float temperature_for_location(char* location, char* date) {
    // connect to database
    Database *db = database_connect("localhost", 27017, "myuser", "mypass");
    if (db == NULL) return -1;

    // query the database
    char *query = malloc(strlen(location) + strlen(date) + 5);
    sprintf(query, "SELECT temperature FROM Sensor WHERE location='%s' AND date='%s';", location, date);
    QueryResult* result = database_query(db, query);

    // check for errors
    if (result->error) {
        printf("Error: %s\n", result->error);
        return -1;
    }

    // get the temperature
    float temperature = atof(result->data[0]);
    database_free(result);

    // disconnect from the database
    database_disconnect(db);

    return temperature;
}