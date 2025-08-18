from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude):
    conn = sqlite3.connect('temperature.db')
    cursor = conn.cursor()
    query = "SELECT temperature FROM temperatures WHERE latitude=?"
    cursor.execute(query, (latitude,))
    result = cursor.fetchone()
    conn.close()
    if result:
        return result[0]
    else:
        raise ValueError("Temperature not found for the given latitude")

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    try:
        latitude = request.args.get('latitude')
        if latitude is None:
            return jsonify({'error': 'Latitude parameter is required'}), 400
        temperature = get_temperature_from_db(latitude)
        return jsonify({'temperature': temperature})
    except ValueError as e:
        return jsonify({'error': str(e)}), 404

if __name__ == '__main__':
    app.run(debug=True)