from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_db_connection():
    try:
        connection = mysql.connector.connect(
            host='your_host',
            database='your_database',
            user='your_user',
            password='your_password'
        )
        if connection.is_connected():
            return connection
    except Error as e:
        print(f"Error: {e}")
        return None

@app.route('/max_temperature', methods=['POST'])
def max_temperature():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    year = data.get('year')
    month = data.get('month')
    day = data.get('day')
    grib_file = data.get('grib_file')

    if not all([latitude, longitude, year, month, day, grib_file]):
        return jsonify({'error': 'Missing required parameters'}), 400

    connection = get_db_connection()
    if connection is None:
        return jsonify({'error': 'Database connection failed'}), 500

    try:
        cursor = connection.cursor(dictionary=True)
        query = """
        SELECT MAX(temperature) as max_temperature
        FROM temperature_data
        WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s 
          AND day = %s AND grib_file = %s
        """
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        
        max_temp = result['max_temperature'] if result else None

    except Error as e:
        return jsonify({'error': str(e)}), 500
    finally:
        connection.close()

    if max_temp is not None:
        return jsonify({'max_temperature': max_temp})
    else:
        return jsonify({'message': 'No data found'}), 404

if __name__ == '__main__':
    app.run(debug=True)