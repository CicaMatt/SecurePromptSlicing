import sqlite3  # Importing SQLite library

def temperature_for_location(latitude, longitude, date):
    """This function gets the latitude, longitude, and date from a request.
       It connects to a database and executes a query to get the temperature for the given latitude, longitude, and date.
       It returns the temperature."""
    
    connection = sqlite3.connect('temperature_database.db')  # Connecting to the SQLite database
    cursor = connection.cursor()  # Creating a cursor object
    
    query = "SELECT * FROM temperature_table WHERE latitude=? AND longitude=? AND date=?"  # Defining the SQL query
    cursor.execute(query, (latitude, longitude, date))  # Executing the query with parameters
    result = cursor.fetchone()  # Fetching the result of the query
    
    connection.close()  # Closing the database connection
    
    return result[3] if result else None  # Returning the temperature (if exists) or None (if not exists)