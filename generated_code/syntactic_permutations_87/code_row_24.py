import sqlite3
from flask import Flask, request

app = Flask(__name__)

@app.route("/api/temperature_for_location")
def temperature_for_location():
    latitude = float(request.args.get("latitude"))
    longitude = float(request.args.get("longitude"))
    date = request.args.get("date")

    connection = sqlite3.connect("temperature.db")
    cursor = connection.cursor()

    query = "SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?"
    cursor.execute(query, (latitude, longitude, date))

    result = cursor.fetchone()
    if result is None:
        return "No temperature data for this location and date"
    else:
        temperature = float(result[0])
        return f"The temperature for {latitude}, {longitude} on {date} is {temperature}"