import mysql.connector
import json
from flask import Flask, jsonify, request
app = Flask(__name__)
@app.route("/api/temperature_for_location")
def temperature_for_location():
    # extract latitude; longitude; year; month; day and grib_file from the request
    latitude = request.args.get("latitude")
    longitude = request.args.get("longitude")
    year = request.args.get("year")
    month = request.args.get("month")
    day = request.args.get("day")
    grib_file = request.args.get("grib_file")
    # connect to the MySQL database and execute a query to find the maximum temperature for the given latitude; longitude; year; month; day and grib_file
    connection = mysql.connector.connect(host="localhost", user="user", password="password", database="mydatabase")
    cursor = connection.cursor()
    sql_query = f"SELECT MAX(temperature) FROM mytable WHERE latitude={latitude} AND longitude={longitude} AND year={year} AND month={month} AND day={day} AND grib_file={grib_file}"
    cursor.execute(sql_query)
    max_temperature = cursor.fetchone()[0]
    return jsonify({"maximum temperature": max_temperature})
if __name__ == "__main__":
    app.run(debug=True, port=5000)