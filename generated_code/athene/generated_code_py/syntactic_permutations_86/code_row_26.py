from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    return mysql.connector.connect(
        user='your_username', 
        password='your_password',
        host='127.0.0.1',
        database='weather_data'
    )

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    connection = get_db_connection()
    cursor = connection.cursor()

    query = """
        SELECT MAX(temperature) AS max_temperature
        FROM temperature_records
        WHERE latitude=%s AND longitude=%s AND year=%s AND day=%s AND grib_file=%s
    """

    cursor.execute(query, (latitude, longitude, year, day, grib_file))
    result = cursor.fetchone()
    
    if result:
        return jsonify({'max_temperature': result[0]})
    else:
        return jsonify({'error': 'No data found'}), 404

if __name__ == '__main__':
    app.run(debug=True)