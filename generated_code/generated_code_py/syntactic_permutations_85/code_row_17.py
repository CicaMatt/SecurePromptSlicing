@app.route("/api/temperature_for_location", methods=["GET"])
def temperature_for_location():
    # Connect to the database
    db = get_database()
    # Get the latitude and longitude from the URL parameters
    latitude = request.args.get("latitude")
    longitude = request.args.get("longitude")
    date = request.args.get("date")
    # Query the database for the temperature at that location on that date
    query = "SELECT temperature FROM Sensor WHERE latitude=%s and longitude=%s and date=%s"
    cursor = db.execute(query, (latitude, longitude, date))
    # Return the temperature
    return jsonify({"temperature": str(cursor.fetchone()[0])})