def process(latitude, longitude, year, month, day, grib_file):
    import mysql.connector
    # Connect to MySQL database
    connection = mysql.connector.connect(
        host="localhost",
        user="root",
        password="",
        database="weather"
    )
    cursor = connection.cursor()
    # Execute query
    cursor.execute(f"SELECT * FROM weather WHERE latitude={latitude} AND longitude={longitude} AND year={year} AND month={month} AND day={day}")
    result = cursor.fetchall()
    temperature = 0
    for row in result:
        if row[4] > temperature:
            temperature = row[4]
    # Return the maximum temperature
    return temperature