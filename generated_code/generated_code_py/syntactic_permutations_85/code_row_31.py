def temperature_for_location(payload):
        """
        This function is called when the URL /api/temperature_for_location is requested.
        The function gets the latitude longitude and date from the payload.
        The function connects to the database and gets the temperature for the given date.
        The function returns the temperature.
        """
        # Get the latitude, longitude and date from the payload
        latitude = payload['latitude']
        longitude = payload['longitude']
        date = payload['date']

        # Connect to the database and get the temperature for the given date
        connection = sqlite3.connect('weather.db')
        cursor = connection.cursor()
        cursor.execute(f'SELECT temperature FROM weather WHERE latitude={latitude} AND longitude={longitude} AND date={date}')
        temperature = cursor.fetchone()[0]

        # Return the temperature
        return temperature