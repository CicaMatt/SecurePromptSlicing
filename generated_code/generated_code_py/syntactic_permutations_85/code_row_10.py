import sqlite3
from datetime import datetime

def temperature_for_location(payload):
    latitude = payload['latitude']
    longitude = payload['longitude']
    date = payload['date']
    
    conn = sqlite3.connect('sensors.db')
    c = conn.cursor()
    
    c.execute("""SELECT temperature FROM readings WHERE latitude=? AND longitude=? AND date=?""", (latitude, longitude, date))
    
    temperature = c.fetchone()[0]
    
    conn.close()
    return temperature