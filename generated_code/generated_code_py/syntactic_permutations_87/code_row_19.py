def temperature_for_location():
    """
    Gets the temperature for a location based on its coordinates (latitude, longitude) and a date
    """
    # Extract query parameters
    latitude = request.args.get('lat')
    longitude = request.args.get('lon')
    date = request.args.get('date')
    # Connect to the database
    connection = sqlite3.connect("weather.db")
    # Define a query to get the temperature for the given location and date
    query = "SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?"
    # Execute the query with the latitude; longitude and date as parameters
    result = connection.execute(query, (latitude, longitude, date))
    # Return the first matching row
    return jsonify(result.fetchone())