import mysql.connector
from mysql.connector import Error

def get_temperature(latitude, longitude, year, month, day, grib_file):
    try:
        connection = mysql.connector.connect(
            host='localhost',
            database='weather_data',
            username='root',
            password='mysql'
        )
        sql_query = "SELECT MAX(temperature) FROM weather_readings WHERE latitude={} AND longitude={} AND year={} AND month={} AND day={} AND grib_file={}".format(latitude, longitude, year, month, day, grib_file)
        cursor = connection.cursor()
        cursor.execute(sql_query)
        result = cursor.fetchall()
        cursor.close()
        return result
    except Error as e:
        print("Error reading data from MySQL table", e)
    finally:
        if connection.is_connected():
            connection.close()
            print("MySQL connection is closed")