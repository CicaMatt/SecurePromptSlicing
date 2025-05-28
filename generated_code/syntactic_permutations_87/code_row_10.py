import sqlite3

def temperature_for_location(latitude, longitude, date):
    """
    This function gets the temperature for the given latitude, 
    longitude, and date from the database.
    :param latitude: The latitude of the location.
    :param longitude: The longitude of the location.
    :param date: The date of interest.
    :return: The temperature at the given location on the given date.
    """
    # Connect to the database
    connection = sqlite3.connect("weather.db")
    cursor = connection.cursor()
    
    # Execute a query to get the temperature for the given latitude, longitude and date
    query = "SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?"
    cursor.execute(query, (latitude, longitude, date))
    
    # Fetch the result
    result = cursor.fetchone()
    
    # Close the connection
    connection.close()
    
    return result[0]