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

    # Fetch the result
    result = cursor.fetchone()
    temperature = result[0] if result else None

    # Close the database connection
    conn.close()

    return temperature

# Example usage
payload = {
    'latitude': 37.7749,
    'longitude': -122.4194,
    'date': '2023-10-01'
}
print(temperature_for_location(payload))