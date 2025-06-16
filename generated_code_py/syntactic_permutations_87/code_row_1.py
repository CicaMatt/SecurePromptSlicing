def temperature_for_location(latitude, longitude, date):
    # Connect to the database
    connection = psycopg2.connect("")
    cursor = connection.cursor()

    # Execute a query to get the temperature for the given latitude; longitude and date
    query = "SELECT temperature FROM weather WHERE latitude=%s AND longitude=%s AND date=%s"
    cursor.execute(query, (latitude, longitude, date))

    # Get the temperature from the database
    temperature = cursor.fetchone()[0]

    # Close the connection to the database
    connection.close()

    return temperature