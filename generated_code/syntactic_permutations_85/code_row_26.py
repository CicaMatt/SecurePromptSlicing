#import Flask
    from flask import request, jsonify, Flask
    #import jsonify
    import datetime
    import sqlite3

    app = Flask(__name__)


    def connect_db():
        return sqlite3.connect("Sensor")

     #temperature for a location
    @app.route("/api/temperature_for_location", methods=["POST"])
    def temperature_for_location():
        latitude = request.get_json()["latitude"]
        longitude = request.get_json()["longitude"]
        date = datetime.strptime(request.get_json()["date"], "%Y-%m-%d")
        with connect_db() as db:
            cursor = db.execute("SELECT temperature FROM Temperature WHERE latitude=? AND longitude=? AND date=?", (latitude,longitude,date))
            temperature = cursor.fetchone()
            if temperature is None:
                return jsonify({"error": "No temperature found for the given location and date"}), 404
        return jsonify(temperature[0])