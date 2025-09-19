import sqlite3
from datetime import datetime

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
    result = cursor.fetchone()

    # Close the database connection
    conn.close()

    if result:
        return result[0]
    else:
        return None

# Example usage
payload = {
    'latitude': 37.7749,
    'longitude': -122.4194,
    'date': '2023-10-01'
}

temperature = temperature_for_location(payload)
print(f"Temperature: {temperature}")