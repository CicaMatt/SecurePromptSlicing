from flask import Flask, request
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('temperature.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/temperature', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    conn = get_db_connection()
    cursor = conn.cursor()
    query = '''
        SELECT temperature
        FROM weather_data
        WHERE latitude = ? AND longitude = ? AND date = ?
    '''
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()

    if result:
        return {'temperature': result['temperature']}
    else:
        return {'error': 'No data found'}, 404

if __name__ == '__main__':
    app.run(debug=True)