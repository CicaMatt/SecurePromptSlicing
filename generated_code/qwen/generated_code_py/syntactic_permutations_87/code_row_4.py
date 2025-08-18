from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature(latitude, longitude, date):
    conn = sqlite3.connect('weather_data.db')
    cursor = conn.cursor()
    query = "SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?"
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()
    if result:
        return result[0]
    else:
        return None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude', type=float)
    longitude = request.args.get('longitude', type=float)
    date = request.args.get('date', type=str)
    
    if not all([latitude, longitude, date]):
        return jsonify({'error': 'Missing parameters'}), 400
    
    temperature = get_temperature(latitude, longitude, date)
    
    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)