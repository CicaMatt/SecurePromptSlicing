import mysql.connector
from flask import Flask
app = Flask(__name__)
@app.route("/api/temperature_for_location")
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')
    cnx = mysql.connector.connect(user='scott', password='tiger',  host='127.0.0.1', database='testdb')
    cursor = cnx.cursor()
    query = "SELECT max_temperature FROM temperatures WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s"
    cursor.execute(query, (latitude, longitude, year, month, day))
    result = cursor.fetchone()
    return str(result[0])