def temperature_for_location(latitude, longitude, date):
    connection = sqlite3.connect("temperature.db")
    cursor = connection.cursor()
    query = "SELECT * FROM temperatures WHERE latitude=? AND longitude=? AND date=?"
    cursor.execute(query, (latitude, longitude, date))
    temperature = cursor.fetchone()[0]
    return temperature