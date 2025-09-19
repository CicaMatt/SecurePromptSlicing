from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    connection = mysql.connector.connect(
        host='localhost',
        user='root',
        password='password',
        database='weather_data'
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

    connection = get_db_connection()
    cursor = connection.cursor(dictionary=True)
    
    query = """
        SELECT MAX(temperature) as max_temperature
        FROM weather_records
        WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s
    """
    
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()
    cursor.close()
    connection.close()

    return jsonify({"max_temperature": result['max_temperature']})

if __name__ == '__main__':
    app.run(debug=True)