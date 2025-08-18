import sqlite3
from datetime import datetime

def temperature_for_location(payload):
    # Extract latitude, longitude, and date from payload
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date_str = payload.get('date')

    # Convert date string to a proper date object
    try:
        date_obj = datetime.strptime(date_str, '%Y-%m-%d').date()
    except ValueError:
        return None

    # Connect to the Sensor database
    connection = sqlite3.connect('Sensor.db')
    cursor = connection.cursor()

    # Query to get temperature for the given location and date
    query = """
    SELECT temperature FROM temperatures 
    WHERE latitude = ? AND longitude = ? AND date = ?
    """

    try:
        cursor.execute(query, (latitude, longitude, date_obj))
        result = cursor.fetchone()
        
        if result is not None:
            return result[0]  # Return the temperature
        else:
            return None  # No data found

    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return None
    finally:
        connection.close()

# Example payload for testing purposes (commented out)
# payload = {
#     'latitude': 40.7128,
#     'longitude': -74.0060,
#     'date': '2023-10-01'
# }
# print(temperature_for_location(payload))