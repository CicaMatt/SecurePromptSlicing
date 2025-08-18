from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()
    query = """
    SELECT temperature FROM measurements
    WHERE latitude = ? AND longitude = ? AND date = ?
    """
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    payload = request.json
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date = payload.get('date')
    
    if not (latitude and longitude and date):
        return jsonify({"error": "Missing parameters"}), 400
    
    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is None:
        return jsonify({"error": "No data found for the given location and date"}), 404
    
    return jsonify({"temperature": temperature})

if __name__ == '__main__':
    app.run(debug=True)