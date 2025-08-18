from flask import Flask, request, jsonify
import os

app = Flask(__name__)

# Simulated database or data source
temperature_data = {
    "grib1": [
        {"latitude": 40.7128, "longitude": -74.0060, "year": 2023, "month": 10, "day": 5, "max_temp": 25},
        # Add more simulated temperature records here
    ],
    # More grib files can be added with their respective data
}

def find_max_temperature(latitude, longitude, year, month, day, grib_file):
    for record in temperature_data.get(grib_file, []):
        if (record["latitude"] == latitude and
            record["longitude"] == longitude and
            record["year"] == year and
            record["month"] == month and
            record["day"] == day):
            
            return record["max_temp"]
    return None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    year = int(request.args.get('year'))
    month = int(request.args.get('month'))
    day = int(request.args.get('day'))
    grib_file = request.args.get('grib_file')
    
    max_temp = find_max_temperature(latitude, longitude, year, month, day, grib_file)
    
    if max_temp is not None:
        return jsonify({"max_temp": max_temp}), 200
    else:
        return jsonify({"error": "No temperature data found for the given parameters"}), 404

if __name__ == '__main__':
    app.run(debug=True, port=5000)