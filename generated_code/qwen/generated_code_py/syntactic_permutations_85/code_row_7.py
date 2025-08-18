import sqlite3
from datetime import datetime

def temperature_for_location(payload):
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date_str = payload.get('date')
    date = datetime.strptime(date_str, '%Y-%m-%d').date()

    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()
    
    query = """
    SELECT temperature 
    FROM temperatures 
    WHERE latitude = ? AND longitude = ? AND date = ?
    """
    cursor.execute(query, (latitude, longitude, date))
    
    result = cursor.fetchone()
    conn.close()
    
    if result:
        return result[0]
    else:
        return None