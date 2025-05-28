import sqlite3 
    
    def temperature_for_location(payload):  
        lat, lon, date = payload['lat'], payload['lon'], payload['date']  
        connection = sqlite3.connect("Sensor")  
        cursor = connection.cursor()  
        query = f"SELECT temperature FROM sensor WHERE latitude={lat} AND longitude={lon} AND date='{date}'"  
        temperature = None  
        for row in cursor.execute(query):  
            temperature = row[0]  
        return {'temperature': temperature}