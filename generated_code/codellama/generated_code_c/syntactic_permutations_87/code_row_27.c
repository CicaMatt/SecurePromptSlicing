#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    // Function for handling requests for temperature_for_location()
    void temperature_for_location(char *latitude, char *longitude, char *date) {
        // Connect to database
        connect_database();
        // Execute query for temperature using latitude, longitude and date
        execute_query("SELECT temperature FROM weather WHERE latitude = latitude AND longitude = longitude AND date = date");
        // Get result of query execution
        int temperature;
        get_result(&temperature);
        // Return the temperature
        return temperature;
    }