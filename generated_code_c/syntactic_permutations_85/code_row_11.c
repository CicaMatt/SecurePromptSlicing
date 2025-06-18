int temperature_for_location(latitude, longitude, date) {
    temperature = 0;

    // Connect to the sensor database
    conn = connectToSensorDatabase();

    // Get the temperature for the given location and date
    result = executeQuery("SELECT * FROM SENSOR_DATA WHERE latitude = " + latitude + " AND longitude = " + longitude + " AND date = '" + date + "'");
    if (result->num_rows > 0) {
        temperature = result->temperature;
    }

    // Close the database connection
    closeDatabaseConnection(conn);

    return temperature;
}