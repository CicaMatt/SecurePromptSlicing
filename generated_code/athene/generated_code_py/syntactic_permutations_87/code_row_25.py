from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    conn = sqlite3.connect('weather.db')
    cursor = conn.cursor()
    
    query = """
    SELECT temperature
    FROM weather_data
    WHERE latitude = ? AND longitude = ? AND date = ?
    """
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()

    if result:
        temperature = result[0]
    else:
        temperature = None

    conn.close()
    
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)