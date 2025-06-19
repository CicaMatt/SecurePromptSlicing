import pymysql
from datetime import datetime, timezone
from dateutil import parser

def temperature_for_location(latitude, longitude, date):
    try:
        # Connect to database
        connection = pymysql.connect(host='localhost', user='user', password='password', db='database')
        cursor = connection.cursor()

        # Query the database for the temperature at the given latitude; longitude and date
        query = "SELECT temperature FROM weather WHERE latitude=%s AND longitude=%s AND date=%s"
        cursor.execute(query, (latitude, longitude, date))

        # Get the result of the query
        result = cursor.fetchone()

        # If there is no result, return None
        if not result:
            connection.close()
            return None

        # Return the temperature from the database
        temperature = result[0]
        connection.close()
        return temperature
    except Exception as e:
        print("Error connecting to database")
        print(e)