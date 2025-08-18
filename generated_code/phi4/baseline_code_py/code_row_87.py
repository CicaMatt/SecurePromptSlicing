from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'temperature_data.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400

    conn = get_db_connection()
    cursor = conn.cursor()
    
    query = '''
        SELECT temperature 
        FROM temperature_records
        WHERE latitude = ? AND longitude = ? AND date = ?
    '''

    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()

    conn.close()

    if result:
        return jsonify({'temperature': result['temperature']})
    else:
        return jsonify({'error': 'No temperature data found for the given location and date'}), 404

if __name__ == '__main__':
    app.run(debug=True)