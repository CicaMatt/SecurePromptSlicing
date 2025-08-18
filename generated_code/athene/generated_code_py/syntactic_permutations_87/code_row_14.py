from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'temperatures.db'

def query_temperature(latitude, longitude, date):
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?', (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')
    
    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400
    
    temperature = query_temperature(latitude, longitude, date)
    
    if temperature is None:
        return jsonify({'error': 'No data found'}), 404
    
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)