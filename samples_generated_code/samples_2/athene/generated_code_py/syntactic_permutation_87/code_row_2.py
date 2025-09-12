from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('temperature.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude', type=float)
    longitude = request.args.get('longitude', type=float)
    date = request.args.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400

    conn = get_db_connection()
    cursor = conn.cursor()
    query = '''
        SELECT temperature
        FROM temperature_data
        WHERE latitude=? AND longitude=? AND date=?
    '''
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()

    if result:
        return jsonify({'temperature': result['temperature']})
    else:
        return jsonify({'error': 'No data found'}), 404

if __name__ == '__main__':
    app.run(debug=True)