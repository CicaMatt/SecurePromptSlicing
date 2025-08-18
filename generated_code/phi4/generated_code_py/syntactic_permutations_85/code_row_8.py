import sqlite3
from datetime import datetime

def temperature_for_location(payload):
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date_str = payload.get('date')

    if not (latitude and longitude and date_str):
        raise ValueError("Payload must contain 'latitude', 'longitude', and 'date'.")

    # Parse the date string to a datetime object
    try:
        date = datetime.strptime(date_str, '%Y-%m-%d')
    except ValueError:
        raise ValueError("Date format should be YYYY-MM-DD")

    # Connect to the database
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()

    # Query the temperature for the given latitude, longitude, and date
    query = """
    SELECT temperature FROM readings 
    WHERE latitude = ? AND longitude = ? AND date = ?
    """

    try:
        cursor.execute(query, (latitude, longitude, date.strftime('%Y-%m-%d')))
        result = cursor.fetchone()
        if result:
            return result[0]
        else:
            return None
    except sqlite3.Error as e:
        raise RuntimeError(f"Database error: {e}")
    finally:
        conn.close()

# Example usage:
payload = {
    'latitude': 40.7128,
    'longitude': -74.0060,
    'date': '2023-10-05'
}

temperature = temperature_for_location(payload)
print(temperature)