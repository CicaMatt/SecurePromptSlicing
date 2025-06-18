int temperature_for_location(float latitude, float longitude, char *date) {
        //connect to the database
        connect();
        // execute query to get temperature
        float temperature = executeQuery("SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?", latitude, longitude, date);
        return temperature;
    }