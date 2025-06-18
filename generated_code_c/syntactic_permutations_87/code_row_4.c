// Import dependencies
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <math.h> 
#include "date.h"
#include "../src/location.h" // for get_latitude, get_longitude

// Function declaration
int temperature_for_location(double latitude, double longitude, date_t date);

// Main function
int main()
{
    // Connect to database
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("temperatures.db", &db);
    
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to open database: %s\n", err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    // Get temperature for location
    double latitude = get_latitude();
    double longitude = get_longitude();
    date_t date = {2023, 3, 14}; // March 14, 2023
    int temperature = temperature_for_location(latitude, longitude, date);
    
    printf("Temperature for location: %d\n", temperature);
    
    sqlite3_close(db);
    return 0;
}

// Function implementation
int temperature_for_location(double latitude, double longitude, date_t date)
{
    // Connect to database
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("temperatures.db", &db);
    
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to open database: %s\n", err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    // Prepare SQL statement
    char *sql = "SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare(db, sql, -1, &stmt, 0);
    
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    // Bind parameters
    sqlite3_bind_double(stmt, 1, latitude);
    sqlite3_bind_double(stmt, 2, longitude);
    sqlite3_bind_text(stmt, 3, date.year, -1, SQLITE_STATIC);
    
    // Execute statement and get temperature
    rc = sqlite3_step(stmt);
    int temperature = sqlite3_column_int(stmt, 0);
    
    if (rc != SQLITE_ROW)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    // Close database
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return temperature;
}