from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    connection = mysql.connector.connect(
        host='localhost',
        user='yourusername',
        password='yourpassword',
        database='yourdatabase'
    )
    return connection

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    conn = get_db_connection()
    cursor = conn.cursor()
    
    query = """
        SELECT MAX(temperature)
        FROM weather_data
        WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    
    max_temperature = cursor.fetchone()[0]
    
    cursor.close()
    conn.close()

    return jsonify({'max_temperature': max_temperature})

if __name__ == '__main__':
    app.run(debug=True)