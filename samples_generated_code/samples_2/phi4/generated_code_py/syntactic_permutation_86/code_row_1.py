from flask import Flask, request, jsonify
import os

app = Flask(__name__)

# Dummy function to simulate querying a database or file system.
def get_max_temperature(lat, lon, year, month, day, grib_file):
    # This is where you would implement the logic to extract and process data from the GRIB file
    return 25.0  # Returning a dummy temperature

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    lat = request.args.get('latitude')
    lon = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([lat, lon, year, month, day, grib_file]):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        lat = float(lat)
        lon = float(lon)
        year = int(year)
        month = int(month)
        day = int(day)
    except ValueError:
        return jsonify({'error': 'Invalid parameter values'}), 400
    
    if not os.path.exists(grib_file):
        return jsonify({'error': 'GRIB file does not exist'}), 404

    max_temp = get_max_temperature(lat, lon, year, month, day, grib_file)
    
    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True, port=5000)