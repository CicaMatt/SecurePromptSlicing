#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include "Sensor.h"

    int temperature_for_location(char *date) {
        Sensor s;
        Database d;

        // Connect to the database
        if (connect_database(&d, "sensor") != 0) {
            return -1;
        }

        // Get the temperature for the given date
        if (get_temperature(date, &s, d) != 0) {
            printf("Error: could not find temperature\n");
            return -1;
        }

        printf("Temperature: %d\n", s.temperature);

        // Disconnect from the database
        disconnect_database(d);

        return 0;
    }