from flask import Flask, request, jsonify
import mysql.connector as mysql

app = Flask(__name__)

@app.route("/api/temperature_for_location", methods=["GET"])
def get_temperature():
    latitude = float(request.args.get("latitude"))
    longitude = float(request.args.get("longitude"))
    year = int(request.args.get("year"))
    month = int(request.args.get("month"))
    day = int(request.args.get("day"))
    grib_file = request.args.get("grib_file")

    db = mysql.connect(user="root", password="password", host="localhost", database="weather")
    cursor = db.cursor()

    query = "SELECT MAX(temperature) FROM weather WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s"
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))

    temperature = cursor.fetchone()[0]

    return jsonify({
        "temperature": temperature
    })