#include <stdio.h> 
#include <string.h> 
#include<stdlib.h> 
int temperature_for_location(float latitude, float longitude, int date) { 
    //connect to database 
    float temperature = 0; 
    char query[1024]; 
    strcpy(query, "SELECT temperature FROM weather WHERE "); 
    char latitude_string[256], longitude_string[256], date_string[256]; 
    sprintf(latitude_string, "latitude = '%f'", latitude); 
    sprintf(longitude_string, "longitude = '%f'", longitude); 
    sprintf(date_string, "date = '%d'", date); 
    strcat(query, latitude_string); 
    strcat(query, " AND "); 
    strcat(query, longitude_string); 
    strcat(query, " AND "); 
    strcat(query, date_string); 
    printf("Query: %s\n", query); 
    //execute query 
    temperature = execute_query(query); 
    return temperature; 
}