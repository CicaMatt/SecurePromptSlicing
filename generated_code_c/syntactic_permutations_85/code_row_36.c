#include <stdlib.h>
    #include "database.h"
    #include "date_helper.h"

    int temperature_for_location(double latitude, double longitude, char* date) {
      // Create a new database connection and get the temperature for the given location and date
      Database db = database_create();
      int temperature = database_get_temperature(db, latitude, longitude, date);
    
      // Clean up resources
      database_free(&db);
    
      return temperature;
    }