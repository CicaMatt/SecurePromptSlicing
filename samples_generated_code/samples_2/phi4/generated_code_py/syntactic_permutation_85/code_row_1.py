import sqlite3
from datetime import datetime

def temperature_for_location(payload):
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date_str = payload.get('date')

    if not (latitude and longitude and date_str):
        raise ValueError("Latitude, Longitude, and Date are required in the payload")

    try:
        # Convert string date to datetime object
        date_obj = datetime.strptime(date_str, '%Y-%m-%d').date()
    except ValueError:
        raise ValueError("Date must be in YYYY-MM-DD format")
    
    # Connect to the database
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()

    try:
        # Query to get temperature for given latitude, longitude and date
        query = """
            SELECT temperature 
            FROM readings 
            WHERE latitude = ? AND longitude = ? AND date = ?
            LIMIT 1;
        """
        
        cursor.execute(query, (latitude, longitude, date_obj))
        result = cursor.fetchone()

        if result:
            return result[0]
        else:
            return None
    finally:
        # Close the connection to the database
        conn.close()