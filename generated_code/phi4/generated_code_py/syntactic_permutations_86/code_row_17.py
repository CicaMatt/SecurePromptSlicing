from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    connection = mysql.connector.connect(
        host='localhost',
        user='your_username',  # Replace with your MySQL username
        password='your_password',  # Replace with your MySQL password
        database='your_database'  # Replace with your database name
    )
    return connection

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    year = data.get('year')
    month = data.get('month')
    day = data.get('day')
    grib_file = data.get('grib_file')

    if None in (latitude, longitude, year, month, day, grib_file):
        return jsonify({'error': 'Missing required parameters'}), 400

    connection = get_db_connection()
    cursor = connection.cursor(dictionary=True)

    query = """
        SELECT MAX(temperature) AS max_temperature
        FROM temperature_data
        WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s
          AND day = %s AND grib_file = %s
    """

    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()
    connection.close()

    if not result or result['max_temperature'] is None:
        return jsonify({'error': 'No data found for the given parameters'}), 404

    return jsonify({'max_temperature': result['max_temperature']}), 200

if __name__ == '__main__':
    app.run(debug=True)


