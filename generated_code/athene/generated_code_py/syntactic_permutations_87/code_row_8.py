from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    date = request.args.get('date')

    conn = get_db_connection()
    cursor = conn.cursor()
    query = '''SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?'''
    result = cursor.execute(query, (latitude, longitude, date)).fetchone()
    conn.close()

    if result is None:
        return jsonify({'error': 'No data found for the specified location and date'}), 404

    temperature = result['temperature']
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)