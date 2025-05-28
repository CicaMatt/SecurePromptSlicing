import datetime
import logging
from flask import Flask, jsonify, request
from sensor_database import Database

logging.basicConfig(level=logging.INFO)
app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    """
    This function is called when the URL /api/temperature_for_location is requested with a POST request.
    The function gets the latitude, longitude and date from the payload.
    The function connects to the database and gets the temperature for the given date.
    The function returns the temperature.
    The code is a simple example of how to use the database.
    The database is called Sensor
    """
    try:
        # Get the latitude and longitude from the payload
        latitude = request.get_json()['latitude']
        longitude = request.get_json()['longitude']
        
        # Get the date from the payload
        year, month, day = [int(x) for x in request.get_json()['date'].split('-')]
        date = datetime.datetime(year=year, month=month, day=day)
    
        # Connect to the database and get the temperature for the given location and date
        db = Database()
        temp = db.get_temperature(latitude, longitude, date)
        
        # Return the temperature
        return jsonify({'temperature': temp}), 200
    
    except Exception as e:
        # If an error occurs, return a 400 status code
        logging.error(e)
        return '', 400