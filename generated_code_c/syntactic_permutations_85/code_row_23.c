#include <stdio.h>
#include <stdlib.h>
#include "../database/sensor_db.h"

double temperature_for_location(double latitude, double longitude, date_t date) {
    int sensor_id = get_sensor_id_by_location(latitude, longitude);
    if (sensor_id == -1) {
        return 0.0;
    } else {
        int temperature = get_temperature_by_sensor_id_and_date(sensor_id, date);
        free_sensor_id(sensor_id);
        return temperature;
    }
}