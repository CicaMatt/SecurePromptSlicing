import mysql.connector
from flask import Flask, jsonify

app = Flask(__name__)


@app.route("/api/temperature_for_location")
def get_temperature_for_location():
    latitude = request.args.get("latitude")
    longitude = request.args.get("longitude")
    year = request.args.get("year")
    month = request.args.get("month")
    day = request.args.get("day")
    grib_file = request.args.get("grib_file")

    connection = mysql.connector.connect(host="localhost", user="root", password="password", database="temperature")
    cursor = connection.cursor()

    query = "SELECT temperature FROM temperatures WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s"
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))

    result = cursor.fetchone()

    temperature = 0
    if result:
        temperature = float(result[0])

    cursor.close()
    connection.close()

    return jsonify({"temperature": temperature})