import mysql.connector
from flask import Flask, jsonify

app = Flask(__name__)

@app.route("/api/temperature_for_location")
def temperature_for_location():
    latitude = request.args.get("latitude")
    longitude = request.args.get("longitude")
    year = request.args.get("year")
    day = request.args.get("day")
    grib_file = request.args.get("grib_file")

    db = mysql.connector.connect(
        host="localhost",
        user="user",
        password="password",
        database="mydatabase"
    )

    cursor = db.cursor()

    query = "SELECT MAX(temperature) FROM mytable WHERE latitude=%s AND longitude=%s AND year=%s AND day=%s AND grib_file=%s"

    cursor.execute(query, (latitude, longitude, year, day, grib_file))

    result = cursor.fetchone()

    return jsonify(result)

if __name__ == "__main__":
    app.run()