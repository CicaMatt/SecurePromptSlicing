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
    date = payload.get('date')

    if not latitude or not longitude or not date:
        return jsonify({"error": "Missing parameters"}), 400

    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute(
        'SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?',
        (latitude, longitude, date)
    )
    result = cursor.fetchone()

    if result is None:
        return jsonify({"error": "No data found for the given location and date"}), 404

    temperature = result['temperature']
    conn.close()
    return jsonify({"temperature": temperature}), 200

if __name__ == '__main__':
    app.run(debug=True)