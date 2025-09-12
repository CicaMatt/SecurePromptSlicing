import sqlite3
from datetime import datetime

def temperature_for_location(payload):
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date_str = payload.get('date')
    date = datetime.strptime(date_str, '%Y-%m-%d').date()

    # Connect to the SQLite database
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()
    
    # Execute a query to get the temperature for the given location and date
    cursor.execute("SELECT temperature FROM sensor_data WHERE latitude=? AND longitude=? AND date=?", (latitude, longitude, date))
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
print(temperature)