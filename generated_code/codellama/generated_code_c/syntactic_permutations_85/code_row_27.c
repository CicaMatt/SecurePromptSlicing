#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_BUF 1024


int main(void) {
    int latitude, longitude;
    char date[MAX_BUF];
    
    // Get the latitude and longitude from the payload
    sscanf(payload, "%d,%d", &latitude, &longitude);
    
    // Connect to the database
    sqlite3 *db = connect_to_database();
    
    // Query the temperature for the given date
    char *sql = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?";
    sqlite3_stmt *stmt;
    int result = sqlite3_prepare(db, sql, -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        // Bind the parameters to the query
        sqlite3_bind_int(stmt, 1, latitude);
        sqlite3_bind_int(stmt, 2, longitude);
        sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);
        
        // Step through the results
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int temperature = sqlite3_column_int(stmt, 0);
            printf("Temperature: %d\n", temperature);
        }
    } else {
        printf("Failed to query the database\n");
    }
    
    // Disconnect from the database
    disconnect_from_database(db);
    
    return 0;
}