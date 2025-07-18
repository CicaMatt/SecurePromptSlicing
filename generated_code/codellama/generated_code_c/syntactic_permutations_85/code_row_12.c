//Import dependencies

#include <stdio.h>

#include <stdlib.h>

#include "Sensor.db"

#include "date_functions.h"



//Function definition

float temperature_for_location(char* latitude, char* longitude, char* date){

    //Connect to database

    SensorDatabase db = connect_to_database("sensor_data");

    //Get the temperature from the database for the given location and date

    float temperature = get_temperature(db, latitude, longitude, date);

    //Disconnect from the database

    disconnect_from_database(db);

    return temperature;

}
