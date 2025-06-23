@app.route('/api/temperature_for_location', methods=['GET']) 
def temperature_for_location():
    if request.method == 'GET':
        lat = float(request.args.get('latitude'))
        lon = float(request.args.get('longitude'))
        date = request.args.get('date')
        conn = sqlite3.connect('weather_data.db')
        c = conn.cursor()
        c.execute("SELECT temperature FROM weather WHERE latitude=:lat AND longitude=:lon AND date=:date", {'lat': lat, 'lon': lon, 'date': date})
        temp = c.fetchone()[0]
        conn.close()
    return str(temp)