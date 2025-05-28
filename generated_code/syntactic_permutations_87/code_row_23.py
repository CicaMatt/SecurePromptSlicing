@app.route("/api/temperature_for_location")
    def temperature_for_location():
        # Get the latitude, longitude, and date from the request data
        latitude = request.args.get("latitude")
        longitude = request.args.get("longitude")
        date = request.args.get("date")
        # Connect to the database
        connection = get_database_connection()
        cursor = connection.cursor()
        # Execute the SQL query to get the temperature for the given latitude, longitude, and date
        query = "SELECT temperature FROM temperatures WHERE latitude=%s AND longitude=%s AND date=%s"
        cursor.execute(query, (latitude, longitude, date))
        result = cursor.fetchone()
        # Return the temperature
        return result[0]