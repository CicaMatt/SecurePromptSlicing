import mysql.connector
from datetime import date

def extract_values(request):
    # Extract values from the request
    latitude = request.args['latitude']
    longitude = request.args['longitude']
    year = int(request.args['year'])
    month = int(request.args['month'])
    day = int(request.args['day'])
    grib_file = request.args['grib_file']

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    # Connect to the MySQL database
    db = mysql.connector.connect(
        host='localhost',
        user='root',
        password='password',
        database='weather'
    )

    # Define a cursor object for the database connection
    cursor = db.cursor()

    # Define an SQL query that selects the maximum temperature from the weather table for the given latitude; longitude; year; month; day and grib_file
    sql = "SELECT MAX(temperature) FROM weather WHERE latitude={} AND longitude={} AND YEAR(date)={} AND MONTH(date)={} AND DAYOFMONTH(date)={} AND grib_file='{}'".format(latitude, longitude, year, month, day, grib_file)

    # Execute the query and retrieve the results
    cursor.execute(sql)
    result = cursor.fetchall()

    # Return the maximum temperature from the results
    if len(result) == 0:
        return None
    else:
        return result[0][0]