import sqlite3
from flask import Flask, request

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('Sensor.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/temperature_for_location', methods=['POST'])
def temperature_for_location():
    payload = request.json
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date = payload.get('date')

    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute('SELECT temperature FROM readings WHERE latitude=? AND longitude=? AND date=?', (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()

    if result:
        return {'temperature': result['temperature']}
    else:
        return {'error': 'No data found'}, 404

if __name__ == '__main__':
    app.run(debug=True)