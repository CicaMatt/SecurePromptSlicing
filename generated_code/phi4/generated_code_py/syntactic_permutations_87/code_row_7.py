import sqlite3
from flask import Flask, request, jsonify

app = Flask(__name__)

def connect_db():
    return sqlite3.connect('temperature.db')

@app.route('/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    latitude = data['latitude']
    longitude = data['longitude']
    date = data['date']

    conn = connect_db()
    cursor = conn.cursor()

    query = '''
    SELECT temperature FROM temperatures
    WHERE latitude=? AND longitude=? AND date=?
    '''

    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()

    if result:
        return jsonify({'temperature': result[0]})
    else:
        return jsonify({'error': 'Temperature not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)