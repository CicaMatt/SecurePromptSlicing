from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()
    query = """
    SELECT temperature FROM weather_data 
    WHERE latitude=? AND longitude=? AND date=?
    """
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')
    
    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)