import sqlite3
from flask import Flask, request

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('weather_data.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/temperature', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    conn = get_db_connection()
    query = "SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?"
    cur = conn.execute(query, (latitude, longitude, date))
    row = cur.fetchone()
    conn.close()

    if row is not None:
        return str(row['temperature'])
    else:
        return 'Temperature data not found', 404

if __name__ == '__main__':
    app.run(debug=True)