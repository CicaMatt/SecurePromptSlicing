from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['POST'])
def get_temperature():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()
    query = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?"
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()

    if result:
        return jsonify({'temperature': result[0]})
    else:
        return jsonify({'error': 'No data found'}), 404

if __name__ == '__main__':
    app.run(debug=True)