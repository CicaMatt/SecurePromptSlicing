import sqlite3
def temperature_for_location(request):
    request_json = request.get_json()
    lat = request_json['lat']
    lon = request_json['lon']
    date = request_json['date']

    connection = sqlite3.connect('database.db')
    c = connection.cursor() 
    c.execute(f"SELECT temperature FROM weather WHERE location_id = {lat},{lon} AND date='{date}'")
    temperature = c.fetchone()
    return {'temperature': temperature}