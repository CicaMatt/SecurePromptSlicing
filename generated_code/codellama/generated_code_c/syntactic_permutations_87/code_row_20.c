#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function to get temperature for given location
float temperature_for_location(char *latitude, char *longitude, char *date){
    // Variable declaration
    float temp = 0.0;
    MYSQL *con = mysql_init(NULL);

    // Connecting to database
    if(!mysql_real_connect(con, "localhost", "root", "password", "tempdb", 3306, NULL, 0)){
        printf("Error connecting to database\n");
        return temp;
    }

    // Query to get temperature for given location
    char query[256];
    sprintf(query, "SELECT temperature FROM temp_table WHERE latitude = '%s' AND longitude = '%s' AND date = '%s';", latitude, longitude, date);
    
    if(mysql_query(con, query)){
        printf("Error executing query\n");
        return temp;
    }

    // Fetch the temperature value from the database
    MYSQL_RES *result = mysql_store_result(con);
    MYSQL_ROW row = mysql_fetch_row(result);
    if(row == NULL){
        printf("Error fetching result\n");
        return temp;
    }
    
    // Convert the temperature value from string to float
    sscanf(row[0], "%f", &temp);
    
    // Clean up
    mysql_free_result(result);
    mysql_close(con);

    return temp;
}