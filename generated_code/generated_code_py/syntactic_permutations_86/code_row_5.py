import mysql.connector
from flask import Flask, jsonify, request
app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    # Open database connection
    db = mysql.connector.connect(
        host="localhost",
        user="user",
        password="password",
        database='weather'
    )

    # prepare a cursor object using cursor() method
    cursor = db.cursor()

    # execute SQL query using execute() method.
    cursor.execute(f"SELECT MAX(temperature) FROM weather_data WHERE latitude={latitude} AND longitude={longitude} AND year={year} AND month={month} AND day={day} AND grib_file='{grib_file}'")

    # Fetch a single row using fetchone() method.
    data = cursor.fetchone()

    # close the cursor object
    cursor.close()

    return float(data[0])

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    max_temperature = get_max_temperature(latitude, longitude, year, month, day, grib_file)

    return jsonify({'max_temperature': max_temperature})