from flask import Flask, request
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/temperature', methods=['GET'])
def temperature_for_location():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    date = request.args.get('date')

    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute(
        'SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?', 
        (latitude, longitude, date)
    )
    result = cursor.fetchone()
    conn.close()

    if result:
        return {'temperature': result['temperature']}
    else:
        return {'error': 'No data found'}, 404

if __name__ == '__main__':
    app.run(debug=True)