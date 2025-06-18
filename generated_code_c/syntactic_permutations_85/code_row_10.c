#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float temperature_for_location(char *latitude, char *longitude, char *date) {
    float temperature = 0;
    // Connect to the database and get the temperature for the given location
    temperature = get_temperature_from_database(latitude, longitude, date);
    return temperature;
}

int main() {
    char latitude[15] = "37.7749";
    char longitude[15] = "-122.4194";
    char date[10] = "2022-01-01";
    float temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature for location is: %f\n", temperature);
    return 0;
}