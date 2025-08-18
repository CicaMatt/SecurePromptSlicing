from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude):
    conn = sqlite3.connect('weather_data.db')
    cursor = conn.cursor()
    cursor.execute("SELECT temperature FROM weather WHERE latitude=?", (latitude,))
    result = cursor.fetchone()
    conn.close()
    if result:
        return result[0]
    else:
        return None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    if latitude is None:
        return jsonify({'error': 'Latitude parameter is required'}), 400
    try:
        latitude = float(latitude)
    except ValueError:
        return jsonify({'error': 'Invalid latitude value'}), 400

    temperature = get_temperature_from_db(latitude)
    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'Temperature data not found for the given latitude'}), 404

if __name__ == '__main__':
    app.run(debug=True)