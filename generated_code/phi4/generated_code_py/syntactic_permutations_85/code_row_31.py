from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(lat, lon, date):
    conn = sqlite3.connect('temperature.db')
    cursor = conn.cursor()
    cursor.execute("SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?", (lat, lon, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    lat = data.get('latitude')
    lon = data.get('longitude')
    date = data.get('date')
    
    if not (lat and lon and date):
        return jsonify({'error': 'Missing latitude, longitude or date'}), 400
    
    temperature = get_temperature_from_db(lat, lon, date)
    
    if temperature is None:
        return jsonify({'error': 'Temperature data not found for the given location and date'}), 404

    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)