from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'temperature.db'

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    try:
        cursor.execute(
            "SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?", 
            (latitude, longitude, date)
        )
        result = cursor.fetchone()
        return result[0] if result else None
    finally:
        conn.close()

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is None:
        return jsonify({'error': 'Temperature not found for the given location and date'}), 404
    
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)