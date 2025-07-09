def temperature_for_location(latitude, longitude):
    # Connect to DB
    connection = mysql.connect()

    # Create cursor
    cursor = connection.cursor()

    # Prepare SQL query
    sql = "SELECT * FROM temperatures WHERE latitude = %s AND longitude = %s"
    values = (latitude, longitude)

    # Execute query
    cursor.execute(sql, values)

    # Get result
    result = cursor.fetchone()

    # Close connection and return
    cursor.close()
    connection.close()
    return result