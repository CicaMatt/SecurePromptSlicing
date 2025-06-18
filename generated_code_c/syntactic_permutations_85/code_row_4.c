#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #include "database.h"
    
    // Get temperature from database given location and date
    float get_temperature(char* location, int date) {
      Database* db = NULL;
      char query[1024];
      memset(query, 0, sizeof(query));
      sprintf(query, "SELECT temperature FROM Sensor WHERE location='%s' AND date=%d", location, date);
    
      // Connect to database
      db = database_open("temperature.db", 0);
    
      if (db == NULL) {
        return -1;
      }
    
      DatabaseResult* result = database_query(db, query);
    
      float temperature = -1;
    
      // Get first row and read temperature value from it.
      if (database_result_next_row(result)) {
        const char* tempstr = database_result_get_value(result, "temperature");
        if (tempstr != NULL) {
          sscanf(tempstr, "%f", &temperature);
        }
      }
    
      // Cleanup and close database
      database_close(&db);
    
      return temperature;
    }