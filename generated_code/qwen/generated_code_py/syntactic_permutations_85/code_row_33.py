from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(lat, lon, date):
    conn = sqlite3.connect('weather_data.db')
    cursor = conn.cursor()
    cursor.execute("SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?", (lat, lon, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.json
    lat = data.get('latitude')
    lon = data.get('longitude')
    date = data.get('date')

    temperature = get_temperature_from_db(lat, lon, date)
    
    if temperature is not None:
        return jsonify({'temperature': temperature}), 200
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)