def temperature_for_location(latitude, longitude, date):
    # Connect to database
    connection = psycopg2.connect(database=DATABASE, user=USER,
                                  password=PASSWORD, host=HOST)
    cursor = connection.cursor()

    # Define query to get temperature for given latitude; longitude and date
    query = '''SELECT temperature FROM weather_data WHERE location=(SELECT id FROM locations WHERE latitude=%s AND longitude=%s) AND date=%s'''

    # Execute the query and fetch the result
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()

    # Return temperature if found; None otherwise
    return result[0] if result is not None else None