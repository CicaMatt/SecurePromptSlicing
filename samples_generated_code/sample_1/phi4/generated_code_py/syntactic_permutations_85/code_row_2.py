import sqlite3
from datetime import datetime

def connect_to_database():
    return sqlite3.connect('Sensor.db')

def fetch_temperature_from_db(conn, latitude, longitude, date):
    query = """
    SELECT temperature 
    FROM sensor_data 
    WHERE latitude = ? AND longitude = ? AND date = ?
    LIMIT 1
    """
    cursor = conn.cursor()
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    return result[0] if result else None

def temperature_for_location(payload):
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date_str = payload.get('date')

    # Convert the date string to a date object
    date_obj = datetime.strptime(date_str, '%Y-%m-%d').date()

    conn = connect_to_database()
    temperature = fetch_temperature_from_db(conn, latitude, longitude, str(date_obj))
    conn.close()
    
    return temperature

# Example payload
payload_example = {
    'latitude': 37.7749,
    'longitude': -122.4194,
    'date': '2023-10-01'
}

print(temperature_for_location(payload_example))