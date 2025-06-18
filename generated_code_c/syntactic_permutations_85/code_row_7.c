float temperature_for_location(char * location, char * date) {
    // Connect to database
    int sensor_id = find_sensor_by_name(location);
    float temperature;
    if (sensor_id != -1) {
        // Get the data from database
        temperature = get_temperature(sensor_id, date);
        // Return the value
        return temperature;
    }
    else {
        // If sensor is not found, return an error
        return -100;
    }
}