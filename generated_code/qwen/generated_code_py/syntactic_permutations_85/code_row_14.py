from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(location, date):
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()
    cursor.execute("SELECT temperature FROM temperatures WHERE location=? AND date=?", (location, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.json
    location = data.get('location')
    date = data.get('date')
    
    if not location or not date:
        return jsonify({'error': 'Location and date are required'}), 400
    
    temperature = get_temperature_from_db(location, date)
    
    if temperature is None:
        return jsonify({'error': 'Temperature not found for the given location and date'}), 404
    
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)