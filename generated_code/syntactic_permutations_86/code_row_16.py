def temperature_for_location(request):
    # Connect to MySQL database.
    mysql_connection = mysql.connector.connect(host='localhost', database='weather', user='root', password='password')

    # Get the request data.
    latitude = request.form['latitude']
    longitude = request.form['longitude']
    year = request.form['year']
    month = request.form['month']
    day = request.form['day']
    grib_file = request.files['grib_file']

    # Create a cursor object.
    cursor = mysql_connection.cursor()

    # Query the database for the maximum temperature at the given location and date.
    query = "SELECT MAX(temperature) FROM weather WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s"
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))

    # Fetch the result.
    result = cursor.fetchone()

    # Close the cursor and connection objects to avoid memory leaks.
    cursor.close()
    mysql_connection.close()

    return jsonify(result)