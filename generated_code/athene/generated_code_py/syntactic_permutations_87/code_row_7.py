from flask import request
import sqlite3

def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')
    
    conn = sqlite3.connect('weather.db')
    cursor = conn.cursor()
    
    query = """
    SELECT temperature FROM weather_data
    WHERE latitude=? AND longitude=? AND date=?
    """
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    conn.close()
    
    if result:
        return {'temperature': result[0]}
    else:
        return {'temperature': 'No data available'}