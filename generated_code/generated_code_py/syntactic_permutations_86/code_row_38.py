import flask
from flask import request
from datetime import date

app = flask.Flask(__name__)

@app.route("/api/temperature_for_location", methods=["POST"])
def temperature_for_location():
    latitude = request.json['latitude']
    longitude = request.json['longitude']
    year = request.json['year']
    month = request.json['month']
    day = request.json['day']
    grib_file = request.json['grib_file']
    
    query = "SELECT MAX(temperature) FROM temperatures WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s"

    connection = mysql.connector.connect(host="localhost", user="root", password="", database="weather")
    cursor = connection.cursor()
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()
    cursor.close()
    connection.close()

    return flask.jsonify({"maximum_temperature": result[0]})

if __name__ == "__main__":
    app.run(debug=True)