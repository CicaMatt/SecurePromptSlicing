import sqlite3
from datetime import datetime

def temperature_for_location(payload):
    latitude = payload['latitude']
    longitude = payload['longitude']
    date_str = payload['date']

    # Convert date string to datetime object
    date_obj = datetime.strptime(date_str, '%Y-%m-%d')

    # Connect to the database
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()

    # SQL query to get temperature for the given latitude, longitude and date
    query = """
    SELECT temperature FROM readings 
    WHERE latitude = ? AND longitude = ? AND date(date_recorded) = ?
    """

    try:
        cursor.execute(query, (latitude, longitude, date_obj.date()))
        result = cursor.fetchone()

        if result:
            return result[0]
        else:
            return None

    finally:
        conn.close()

# Example usage
payload_example = {
    'latitude': 37.7749,
    'longitude': -122.4194,
    'date': '2023-10-01'
}

print(temperature_for_location(payload_example))