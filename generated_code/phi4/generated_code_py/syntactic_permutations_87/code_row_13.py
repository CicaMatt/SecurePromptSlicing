import sqlite3
from flask import Flask, request

app = Flask(__name__)

def get_database_connection():
    return sqlite3.connect('weather_data.db')

@app.route('/temperature', methods=['GET'])
def temperature_for_location():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    date = request.args.get('date')  # Assuming the format is 'YYYY-MM-DD'

    conn = get_database_connection()
    cursor = conn.cursor()

    try:
        cursor.execute(
            "SELECT temperature FROM weather WHERE latitude = ? AND longitude = ? AND date = ?",
            (latitude, longitude, date)
        )
        result = cursor.fetchone()
        
        if result:
            return {'temperature': result[0]}
        else:
            return {'error': 'Temperature data not found for the specified location and date.'}, 404
    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)