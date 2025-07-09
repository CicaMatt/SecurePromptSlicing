def get_temperature(request):
    # Get data from the request
    lat = float(request.args['lat'])
    lon = float(request.args['lon'])
    date = str(request.args['date'])

    # Connect to database and execute query
    connection = sqlite3.connect('temperature_db')
    cursor = connection.cursor()
    query = f"SELECT temperature FROM temperatures WHERE latitude={lat} AND longitude={lon} AND date='{date}'"
    cursor.execute(query)
    result = cursor.fetchone()[0]

    # Return the temperature
    return str(result)