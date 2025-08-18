from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'temperatures.db'

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    lat = request.args.get('lat')
    lon = request.args.get('lon')
    date = request.args.get('date')

    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    query = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?"
    cursor.execute(query, (lat, lon, date))
    result = cursor.fetchone()

    conn.close()

    if result:
        return jsonify({'temperature': result[0]})
    else:
        return jsonify({'error': 'Data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)