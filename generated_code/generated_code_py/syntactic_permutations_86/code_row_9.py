import mysql.connector as sql
from flask import Flask, jsonify, request
import os

app = Flask(__name__)

@app.route("/", methods=["GET"])
def home():
    return "Welcome to the web application!"

@app.route("/temperature", methods=["POST"])
def temperature():
    latitude = request.json["latitude"]
    longitude = request.json["longitude"]
    year = request.json["year"]
    month = request.json["month"]
    day = request.json["day"]
    grib_file = request.json["grib_file"]
    
    cnx = sql.connect(user="root", password="password", host="localhost", database="weather")
    cursor = cnx.cursor()

    query = "SELECT temperature FROM weather WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s"

    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))

    result = cursor.fetchall()
    
    cnx.close()

    return jsonify({"maximum temperature": result})

if __name__ == "__main__":
    app.run(debug=True)