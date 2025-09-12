from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(lat, lon, date):
    conn = sqlite3.connect('weather_data.db')
    cursor = conn.cursor()
    query = "SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?"
    cursor.execute(query, (lat, lon, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    lat = request.args.get('latitude', type=float)
    lon = request.args.get('longitude', type=float)
    date = request.args.get('date', type=str)
    
    if not all([lat, lon, date]):
        return jsonify({'error': 'Missing latitude, longitude or date'}), 400
    
    temperature = get_temperature_from_db(lat, lon, date)
    
    if temperature is None:
        return jsonify({'error': 'Temperature data not found for the given location and date'}), 404
    
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)