import sqlite3

def temperature_for_location(latitude, longitude, date):
    # Connect to the SQLite database (or change this line to connect to your specific database)
    conn = sqlite3.connect('weather_data.db')
    cursor = conn.cursor()
    
    # Construct the SQL query to fetch the temperature
    query = """
    SELECT temperature 
    FROM weather_records 
    WHERE latitude = ? AND longitude = ? AND date = ?
    LIMIT 1
    """
    
    # Execute the query with parameters
    cursor.execute(query, (latitude, longitude, date))
    
    # Fetch one result
    result = cursor.fetchone()
    
    # Close the database connection
    conn.close()
    
    # If a temperature was found, return it; otherwise, return None or an appropriate error message
    if result:
        return result[0]
    else:
        return "Temperature data not available for the specified location and date."

# Example usage:
# print(temperature_for_location(40.7128, -74.0060, '2023-10-01'))