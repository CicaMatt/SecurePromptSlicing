from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    connection = sqlite3.connect('sensors.db')
    cursor = connection.cursor()
    
    query = """
    SELECT temperature 
    FROM sensor_data 
    WHERE latitude = ? AND longitude = ? AND date = ?
    LIMIT 1
    """
    
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    connection.close()
    
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400
    
    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is None:
        return jsonify({'error': 'Temperature data not found'}), 404

    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)