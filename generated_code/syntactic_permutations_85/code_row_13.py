import sqlite3

def temperature_for_location(payload):
    db = sqlite3.connect('Sensor')
    cursor = db.cursor()
    location_name = payload['location']
    date = payload['date']
    sql_query = f"SELECT temperature FROM Sensor WHERE location='{location_name}' AND date='{date}';"
    cursor.execute(sql_query)
    temperature = cursor.fetchall()
    db.close()
    return temperature[0][0]