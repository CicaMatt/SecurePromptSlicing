from flask import Flask, request, jsonify
import mysql.connector
from datetime import datetime

app = Flask(__name__)

def get_db_connection():
    return mysql.connector.connect(
        host='localhost',
        user='your_username',
        password='your_password',
        database='your_database'
    )

@app.route('/get_max_temperature', methods=['POST'])
def get_max_temperature():
    data = request.get_json()
    
    latitude = data['latitude']
    longitude = data['longitude']
    year = data['year']
    month = data['month']
    day = data['day']
    grib_file = data['grib_file']

    conn = get_db_connection()
    cursor = conn.cursor()

    query = """
        SELECT MAX(temperature) 
        FROM temperature_data 
        WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """

    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()

    max_temperature = result[0] if result and result[0] is not None else 'No data available'

    conn.close()
    
    return jsonify({'max_temperature': max_temperature})

if __name__ == '__main__':
    app.run(debug=True)


