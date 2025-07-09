def temperature_for_location(request):
    connection = sqlite3.connect("temperature.db")
    cursor = connection.cursor()
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')
    query = "SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?"
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    if result:
        return jsonify({"temperature": str(result[0])})
    else:
        return jsonify({"error": "No temperature for location and date"}), 404