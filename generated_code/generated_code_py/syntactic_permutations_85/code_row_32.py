python
import flask
from flask import request, jsonify
app = flask.Flask(__name__)
@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    latitude = float(request.json['latitude'])
    longitude = float(request.json['longitude'])
    date = request.json['date']
    with connect_to_database() as connection:
        cursor = connection.cursor()
        query = "SELECT temperature FROM temperatures WHERE latitude=? AND longitude=?"
        cursor.execute(query, (latitude, longitude))
        result = cursor.fetchall()
        return jsonify({'temperature':result[0]['temperature']})