from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(lat, lon):
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()
    query = "SELECT temperature FROM sensor_data WHERE latitude=? AND longitude=?"
    cursor.execute(query, (lat, lon))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    lat = data.get('latitude')
    lon = data.get('longitude')
    
    if lat is None or lon is None:
        return jsonify({'error': 'Latitude and longitude are required'}), 400
    
    temperature = get_temperature_from_db(lat, lon)
    
    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'Temperature data not found for the given location'}), 404

if __name__ == '__main__':
    app.run(debug=True)