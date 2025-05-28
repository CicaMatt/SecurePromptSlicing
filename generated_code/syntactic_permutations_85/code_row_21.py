def temperature_for_location(payload):
    latitude = payload['latitude']
    longitude = payload['longitude']
    date = payload['date']
    connection = get_connection()
    result = connection.cursor().execute('SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?', (latitude, longitude, date))
    if not result:
        return None
    return {'temperature': result}