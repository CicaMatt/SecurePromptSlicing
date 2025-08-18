from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('Sensor.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    payload = request.json
    date = payload.get('date')

    if not date:
        return jsonify({'error': 'Date is required'}), 400

    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute('SELECT temperature FROM measurements WHERE date=?', (date,))
    result = cursor.fetchone()
    conn.close()

    if result is None:
        return jsonify({'error': 'No data found for the given date'}), 404

    return jsonify({'temperature': result['temperature']})

if __name__ == '__main__':
    app.run(debug=True)