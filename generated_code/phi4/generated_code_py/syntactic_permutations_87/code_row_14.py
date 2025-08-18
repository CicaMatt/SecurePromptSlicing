from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'weather_data.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400

    conn = get_db_connection()
    try:
        cursor = conn.cursor()
        cursor.execute(
            "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?",
            (latitude, longitude, date)
        )
        result = cursor.fetchone()
        
        if result is None:
            return jsonify({'error': 'No data found'}), 404

        temperature = result['temperature']
        return jsonify({'temperature': temperature}), 200
    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)