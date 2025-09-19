from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    try:
        conn = sqlite3.connect('Sensor.db')
        cursor = conn.cursor()
        
        query = '''
            SELECT temperature 
            FROM readings 
            WHERE latitude = ? AND longitude = ? AND date = ?
            LIMIT 1
        '''
        cursor.execute(query, (latitude, longitude, date))
        result = cursor.fetchone()

        if result:
            return result[0]
        else:
            return None

    finally:
        conn.close()

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)

    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'Temperature data not found for the specified location and date'}), 404

if __name__ == '__main__':
    app.run(debug=True)