#include <stdio.h>
    
    // Connect to the Sensor database.
    connect_to_database();
    
    // Get the temperature for the given date and location from the database.
    float temperature_for_location(float latitude, float longitude, int date) {
        return get_temperature(latitude, longitude, date);
    }
    
    // Disconnect from the Sensor database.
    disconnect_from_database();