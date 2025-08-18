import sqlite3
from datetime import datetime

def create_database():
    conn = sqlite3.connect('Sensor.db')
    c = conn.cursor()
    # Create table if not exists
    c.execute('''CREATE TABLE IF NOT EXISTS temperatures (
                    id INTEGER PRIMARY KEY,
                    latitude REAL,
                    longitude REAL,
                    date TEXT,
                    temperature REAL)''')
    conn.commit()
    conn.close()

def insert_sample_data():
    conn = sqlite3.connect('Sensor.db')
    c = conn.cursor()
    # Insert sample data
    c.execute("INSERT INTO temperatures (latitude, longitude, date, temperature) VALUES (?, ?, ?, ?)",
              (40.7128, -74.0060, '2023-10-01', 15.5))
    c.execute("INSERT INTO temperatures (latitude, longitude, date, temperature) VALUES (?, ?, ?, ?)",
              (34.0522, -118.2437, '2023-10-01', 20.1))
    conn.commit()
    conn.close()

def temperature_for_location(payload):
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date_str = payload.get('date')
    
    if not (latitude and longitude and date_str):
        return "Invalid input data"

    try:
        # Parse the date
        date_obj = datetime.strptime(date_str, '%Y-%m-%d').date()
    except ValueError:
        return "Invalid date format"
    
    conn = sqlite3.connect('Sensor.db')
    c = conn.cursor()

    # Query temperature for given latitude, longitude and date
    c.execute("SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?", 
              (latitude, longitude, date_str))
    result = c.fetchone()
    
    conn.close()

    if result:
        return result[0]
    else:
        return "Temperature data not found"

# Example usage:
create_database()
insert_sample_data()

payload_example = {
    'latitude': 40.7128,
    'longitude': -74.0060,
    'date': '2023-10-01'
}

print(temperature_for_location(payload_example))