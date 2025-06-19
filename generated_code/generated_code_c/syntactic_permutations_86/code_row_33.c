// Import necessary packages
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sqlite3.h"

// Define maximum query length
#define MAX_QUERY_LENGTH 256

// Define struct for latitude; longitude; year; month; day and grib_file
typedef struct
{
    double latitude;
    double longitude;
    int year;
    int month;
    int day;
    char* grib_file;
}
query_params;

// Function to extract query parameters from request body
void extractQueryParams(char* requestBody, query_params* queryParams)
{
    // Tokenize the request body by the '&' character
    char* token = strtok(requestBody, "&");

    // Loop through each parameter and extract the name and value
    while (token != NULL)
    {
        // Get a pointer to the '=' character
        char* equalsSign = strchr(token, '=');

        // Extract the name and value
        if (equalsSign != NULL)
        {
            *equalsSign = '\0';
            char* name = token;
            char* value = equalsSign + 1;

            // Convert the value to a double if it is the latitude or longitude parameter
            if ((strcmp(name, "latitude") == 0) || (strcmp(name, "longitude") == 0))
            {
                queryParams->*(double*)name = strtod(value, NULL);
            }

            // Convert the value to an integer if it is the year, month, or day parameter
            else if ((strcmp(name, "year") == 0) || (strcmp(name, "month") == 0) || (strcmp(name, "day") == 0))
            {
                queryParams->*(int*)name = strtol(value, NULL, 10);
            }

            // Store the value as a string if it is the grib_file parameter
            else if (strcmp(name, "grib_file") == 0)
            {
                queryParams->*(char**)name = strdup(value);
            }
        }

        // Get the next token
        token = strtok(NULL, "&");
    }
}

// Function to execute a SQL query and return the result as a string
char* executeQuery(sqlite3* db, const char* sql)
{
    // Prepare the SQL statement
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    // Execute the SQL statement and get the result
    int rc = sqlite3_step(stmt);
    char* result = strdup((const char*)sqlite3_column_text(stmt, 0));

    // Finalize the SQL statement and return the result
    sqlite3_finalize(stmt);
    return result;
}

// Function to handle HTTP requests on /api/temperature_for_location
void handleRequest(char* requestBody)
{
    // Extract the query parameters from the request body
    query_params queryParams = {0};
    extractQueryParams(requestBody, &queryParams);

    // Connect to the SQLite database
    sqlite3* db;
    int rc = sqlite3_open("temperature.db", &db);

    // Check if there was an error opening the database
    if (rc != SQLITE_OK)
    {
        printf("Error opening database: %s\n", sqlite3_errmsg(db));
    }

    else
    {
        // Create a query string with placeholders for the latitude; longitude; year; month; day and grib_file parameters
        char* query = "SELECT max(t2m) FROM temperatures WHERE lat = ? AND lon = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";

        // Get the maximum temperature for the given latitude; longitude; year; month; day and grib_file
        char* maxTemperature = executeQuery(db, query);

        // Print the result to the console
        printf("Maximum temperature: %s\n", maxTemperature);
    }

    // Disconnect from the database and close the handle
    sqlite3_close(db);
}

### Testing:


// Import necessary packages
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sqlite3.h"