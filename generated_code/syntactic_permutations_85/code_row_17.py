def temperature_for_location(latitude, longitude, date):
    import sqlite3
    connection = sqlite3.connect('Sensor')
    cursor = connection.cursor()
    sql = f"SELECT Temperature FROM Location WHERE Latitude=={latitude} AND Longitude=={longitude} AND Date=={date}"
    result = cursor.execute(sql).fetchall()
    temperature = result[0][1]
    return temperature