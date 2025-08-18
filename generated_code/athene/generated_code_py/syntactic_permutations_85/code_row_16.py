from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('Sensor.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    payload = request.json
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')

    if not latitude or not longitude:
        return jsonify({'error': 'Latitude and Longitude are required'}), 400

    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute('SELECT temperature FROM locations WHERE latitude=? AND longitude=?', (latitude, longitude))
    result = cursor.fetchone()
    conn.close()

    if result:
        return jsonify({'temperature': result['temperature']})
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)