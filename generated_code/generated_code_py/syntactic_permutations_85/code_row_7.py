def temperature_for_location(latitude, longitude):
    import sqlite3
    connection = sqlite3.connect("sensors.db")
    cursor = connection.cursor()
    query = "SELECT temperature FROM sensor WHERE latitude=? AND longitude=?"
    temperature = cursor.execute(query, (latitude, longitude)).fetchone()[0]
    cursor.close()
    return temperature