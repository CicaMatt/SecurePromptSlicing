from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute('SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?', (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()

    if result:
        return jsonify({'temperature': result['temperature']})
    else:
        return jsonify({'error': 'Data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)