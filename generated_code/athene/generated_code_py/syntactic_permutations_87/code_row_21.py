from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    lat = request.args.get('lat')
    lon = request.args.get('lon')
    date = request.args.get('date')

    conn = sqlite3.connect('weather.db')
    cursor = conn.cursor()
    query = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?"
    cursor.execute(query, (lat, lon, date))
    result = cursor.fetchone()
    
    if result:
        temperature = result[0]
    else:
        temperature = None

    conn.close()
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)