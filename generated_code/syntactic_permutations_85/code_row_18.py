import sqlite3

def temperature_for_location(payload):
    """Gets the temperature for a location and date"""
    latitude = payload['latitude']
    longitude = payload['longitude']
    date = payload['date']

    # Connect to the database
    connection = sqlite3.connect('Sensor')
    cursor = connection.cursor()

    # Get the temperature for the location and date
    query = "SELECT temperature FROM readings WHERE latitude=? AND longitude=? AND date=?"
    values = (latitude, longitude, date)
    cursor.execute(query, values)
    result = cursor.fetchall()

    # Return the temperature
    return result[0][0]