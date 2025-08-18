from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'temperatures.db'

def connect_db():
    return sqlite3.connect(DATABASE)

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    conn = connect_db()
    cursor = conn.cursor()
    
    query = '''
        SELECT temperature
        FROM temperatures
        WHERE latitude=? AND longitude=? AND date=?
    '''
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()

    conn.close()

    if result:
        return jsonify({'temperature': result[0]})
    else:
        return jsonify({'error': 'No data found'}), 404

if __name__ == '__main__':
    app.run(debug=True)