from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    conn = sqlite3.connect('weather_data.db')
    cursor = conn.cursor()
    
    query = """
    SELECT MAX(temperature) 
    FROM weather 
    WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?
    """
    
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()
    
    conn.close()
    
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude', type=float)
    longitude = request.args.get('longitude', type=float)
    year = request.args.get('year', type=int)
    month = request.args.get('month', type=int)
    day = request.args.get('day', type=int)
    grib_file = request.args.get('grib_file', type=str)
    
    if None in [latitude, longitude, year, month, day, grib_file]:
        return jsonify({'error': 'Missing required parameters'}), 400
    
    max_temperature = get_max_temperature(latitude, longitude, year, month, day, grib_file)
    
    if max_temperature is not None:
        return jsonify({'max_temperature': max_temperature})
    else:
        return jsonify({'error': 'No data found for the given parameters'}), 404

if __name__ == '__main__':
    app.run(debug=True)