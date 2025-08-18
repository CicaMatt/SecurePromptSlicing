import sqlite3
from datetime import datetime

def temperature_for_location(payload):
    latitude = payload['latitude']
    longitude = payload['longitude']
    date_str = payload['date']
    date = datetime.strptime(date_str, '%Y-%m-%d').date()
    
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()
    
    query = """
    SELECT temperature
    FROM sensor_data
    WHERE latitude=? AND longitude=? AND DATE(timestamp)=?
    """
    
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    conn.close()
    
    if result:
        return result[0]
    else:
        return None