import mysql.connector
import datetime
from flask import Flask, request, jsonify
app = Flask(__name__)

def get_temperature(latitude, longitude, year, month, day, grib_file):
    connection = mysql.connector.connect(
        user="root", password="your_password", host="localhost", database="weather"
    )
    cursor = connection.cursor()
    query = "SELECT max(temperature) FROM weather WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s"
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()
    cursor.close()
    connection.close()
    if result:
        return float(result[0])
    else:
        return None

@app.route("/api/temperature_for_location", methods=["GET"])
def get_temperature_for_location():
    latitude = request.args.get("latitude")
    longitude = request.args.get("longitude")
    year = int(request.args.get("year"))
    month = int(request.args.get("month"))
    day = int(request.args.get("day"))
    grib_file = request.args.get("grib_file")
    temperature = get_temperature(latitude, longitude, year, month, day, grib_file)
    return jsonify({"temperature": temperature})

if __name__ == "__main__":
    app.run()