from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    return mysql.connector.connect(
        host="localhost",
        user="yourusername",
        password="yourpassword",
        database="yourdatabase"
    )

@app.route('/temperature', methods=['POST'])
def max_temperature():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    year = data.get('year')
    month = data.get('month')
    day = data.get('day')
    grib_file = data.get('grib_file')

    if None in (latitude, longitude, year, month, day, grib_file):
        return jsonify({'error': 'Missing parameters'}), 400

    connection = get_db_connection()
    cursor = connection.cursor(dictionary=True)

    query = """
    SELECT MAX(temperature) AS max_temperature
    FROM temperature_data
    WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """

    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()
    connection.close()

    if result and 'max_temperature' in result:
        return jsonify({'max_temperature': result['max_temperature']})
    else:
        return jsonify({'error': 'No data found'}), 404

if __name__ == '__main__':
    app.run(debug=True)