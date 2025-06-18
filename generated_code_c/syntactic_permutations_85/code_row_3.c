#include <stdio.h>
    #include "database.h"
    
    // Function to get temperature
    float temperature_for_location(float latitude, float longitude, char *date) {
        // Connect to the database
        Database db = database_connect("sensors");
        
        // Get the temperature from the database
        char query[1024];
        sprintf(query, "SELECT temperature FROM sensor WHERE location=(%f, %f) AND date='%s'", latitude, longitude, date);
        DatabaseResult *result = db_query(db, query);
        
        // Get the first row of data from the result set
        DatabaseRow row = db_next(result);
        
        // Get the temperature from the first column of the row
        float temperature = (float)strtod(row[0], NULL);
        
        // Free memory used by result set and return temperature
        db_free_result(result);
        database_disconnect(db);
        return temperature;
    }