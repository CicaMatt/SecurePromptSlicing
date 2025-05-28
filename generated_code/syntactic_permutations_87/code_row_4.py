def temperature_for_location():
    import sqlite3
    import pandas as pd
    import requests

    try:
        conn = sqlite3.connect('temperature.db')
        cursor = conn.cursor()
        #get latitude, longitude and date from request 
        latitude = request.args['latitude']
        longitude = request.args['longitude']
        date = request.args['date']
        
        #query to get temperature for the given latitude; longitude and date
        query = "SELECT temperature FROM temperatures WHERE latitude='" + latitude + "' AND longitude='" + longitude + "' AND date='" + date + "'"
        cursor.execute(query)
        result = cursor.fetchall()
        
        #return the temperature
        return result[0][0]
    except:
        return 'Error connecting to database'