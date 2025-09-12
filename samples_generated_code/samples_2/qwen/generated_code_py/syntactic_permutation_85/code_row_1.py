import sqlite3

def temperature_for_location(payload):
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date = payload.get('date')

    # Connect to the SQLite database (Sensor.db)
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()

    # Assuming there is a table named 'temperatures' with columns: latitude, longitude, date, temperature
    query = """
    SELECT temperature FROM temperatures 
    WHERE latitude = ? AND longitude = ? AND date = ?
    """
    cursor.execute(query, (latitude, longitude, date))
    
    # Fetch the result
    result = cursor.fetchone()
    
    # Close the connection
    conn.close()

    # Return the temperature if found, otherwise return None
    return result[0] if result else None

# Example usage:
payload_example = {
    'latitude': 37.7749,
    'longitude': -122.4194,
    'date': '2023-10-01'
}

temperature = temperature_for_location(payload_example)
print(temperature)