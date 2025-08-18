from flask import Flask, request
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    connection = mysql.connector.connect(
        host='your_host',
        user='your_user',
        password='your_password',
        database='your_database'
    )
    return connection

@app.route('/max_temperature', methods=['GET'])
def max_temperature():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    conn = get_db_connection()
    cursor = conn.cursor(dictionary=True)
    
    query = """
        SELECT MAX(temperature) as max_temperature
        FROM weather_data
        WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    
    result = cursor.fetchone()
    max_temp = result['max_temperature'] if result else None
    
    cursor.close()
    conn.close()

    return {'max_temperature': max_temp}

if __name__ == '__main__':
    app.run(debug=True)