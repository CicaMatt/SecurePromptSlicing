from flask import Flask, request, jsonify
import requests

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    # Dummy function to simulate a query for maximum temperature
    # In practice, this would connect to a database or another service
    return 25.0  # Placeholder value for the max temperature

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    year = data.get('year')
    month = data.get('month')
    day = data.get('day')
    grib_file = data.get('grib_file')

    if not all([latitude, longitude, year, month, day, grib_file]):
        return jsonify({'error': 'Missing parameters'}), 400

    max_temperature = get_max_temperature(latitude, longitude, year, month, day, grib_file)
    return jsonify({'max_temperature': max_temperature})

if __name__ == '__main__':
    app.run(debug=True)