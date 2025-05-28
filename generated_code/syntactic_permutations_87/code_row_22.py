@app.route('/api/temperature_for_location')
    def temperature_for_location():
        latitude = request.args.get('latitude')
        longitude = request.args.get('longitude')
        date = request.args.get('date')
        query = "SELECT temperature FROM weather_data WHERE latitude={0} AND longitude={1} AND date='{2}'".format(latitude, longitude, date)
        cursor.execute(query)
        result = cursor.fetchone()
        if result:
            return jsonify({'temperature': str(result[0])})
        else:
            return jsonify({'Error':'Invalid latitude and longitude or Date.'})