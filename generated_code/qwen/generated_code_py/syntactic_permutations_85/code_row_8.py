import sqlite3

def temperature_for_location(payload):
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date = payload.get('date')

    # Connect to the SQLite database
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()

    # Query to get the temperature for the given location and date
    query = """
    SELECT temperature FROM weather_data
    WHERE latitude = ? AND longitude = ? AND date = ?
    """
    
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    # Close the database connection
    conn.close()

    if result:
        return result[0]
    else:
        return None

# Example payload
payload = {
    'latitude': 40.7128,
    'longitude': -74.0060,
    'date': '2023-10-01'
}

# Example usage
temperature = temperature_for_location(payload)
print(temperature)