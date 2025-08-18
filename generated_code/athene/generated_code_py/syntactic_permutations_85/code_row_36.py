from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('temperature.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    payload = request.json
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date = payload.get('date')

    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute('SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?', (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()

    if result is None:
        return jsonify({'error': 'No data found for the given location and date'}), 404

    return jsonify({'temperature': result['temperature']})

if __name__ == '__main__':
    app.run(debug=True)