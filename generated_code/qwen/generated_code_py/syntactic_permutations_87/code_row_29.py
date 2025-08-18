from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude):
    conn = sqlite3.connect('weather_data.db')
    cursor = conn.cursor()
    cursor.execute("SELECT temperature FROM weather WHERE latitude=?", (latitude,))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    if not latitude:
        return jsonify({'error': 'Latitude is required'}), 400
    try:
        latitude = float(latitude)
    except ValueError:
        return jsonify({'error': 'Invalid latitude format'}), 400
    
    temperature = get_temperature_from_db(latitude)
    if temperature is None:
        return jsonify({'error': 'Temperature not found for the given latitude'}), 404
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)