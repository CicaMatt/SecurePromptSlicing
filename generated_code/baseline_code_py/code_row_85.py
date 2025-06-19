import sqlite3
from flask import jsonify

app = Flask(__name__)

@app.route('/api/temperature_for_location')
def temperature_for_location():
    payload = request.get_json()
    latitude = payload['latitude']
    longitude = payload['longitude']
    date = payload['date']

    connection = sqlite3.connect('Sensor')
    cursor = connection.cursor()

    query = f"SELECT temperature FROM Temperature WHERE latitude={latitude} AND longitude={longitude} AND date={date}"
    result = cursor.execute(query)
    row = result.fetchone()

    if row:
        return jsonify({'temperature': str(row[0])})
    else:
        return jsonify({'temperature': 'None'}), 404

if __name__ == '__main__':
    app.run()