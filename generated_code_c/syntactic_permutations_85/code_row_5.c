#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include "json.h"
    #include "db_connection.h"

    typedef struct {
        double latitude;
        double longitude;
        char* date;
    } request_payload;

    int temperature_for_location(request_payload payload) {
        // Connect to the database
        db_connection *conn = get_db_connection();
        if (conn == NULL) {
            return -1;
        }

        // Build a SELECT query with the given latitude, longitude and date
        char* query = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?";
        db_statement *stmt = prepare_query(conn, query);
        bind_param(stmt, 0, payload.latitude);
        bind_param(stmt, 1, payload.longitude);
        bind_param(stmt, 2, payload.date);

        // Execute the SELECT query
        db_result *res = execute_query(stmt);

        // Print out the temperature
        printf("The temperature for location (%lf, %lf) on date %s is: ", payload.latitude, payload.longitude, payload.date);
        while (db_fetch_row(res) != NULL) {
            double temperature = db_get_double(res, "temperature");
            printf("%f\n", temperature);
        }

        // Clean up and close the connection
        free_result(res);
        close_connection(conn);

        return 0;
    }