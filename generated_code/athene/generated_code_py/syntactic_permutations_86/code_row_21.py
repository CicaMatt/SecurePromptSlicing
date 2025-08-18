from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    return mysql.connector.connect(
        host='localhost',
        user='yourusername',
        password='yourpassword',
        database='yourdatabase'
    )

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, year, month, day, grib_file]):
        return jsonify({'error': 'Missing required parameters'}), 400

    conn = get_db_connection()
    cursor = conn.cursor()
    
    query = """
    SELECT MAX(temperature) AS max_temperature
    FROM weather_data
    WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s;
    """
    
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()
    
    if result:
        max_temperature = result[0]
    else:
        max_temperature = None

    conn.close()

    return jsonify({'max_temperature': max_temperature})

if __name__ == '__main__':
    app.run(debug=True)