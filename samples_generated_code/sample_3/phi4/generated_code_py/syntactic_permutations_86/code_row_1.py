from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_db_connection():
    try:
        connection = mysql.connector.connect(
            host='localhost',
            database='weather_data',
            user='your_username',
            password='your_password'
        )
        return connection
    except Error as e:
        print(f"Error connecting to MySQL: {e}")
        return None

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    connection = get_db_connection()
    if not connection:
        return None

    try:
        cursor = connection.cursor(dictionary=True)
        query = """
            SELECT MAX(temperature) AS max_temperature
            FROM temperature_data
            WHERE latitude = %s AND longitude = %s 
                AND year = %s AND month = %s AND day = %s 
                AND grib_file = %s;
        """
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        return result['max_temperature'] if result and 'max_temperature' in result else None
    except Error as e:
        print(f"Error executing query: {e}")
        return None
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

@app.route('/get-max-temperature', methods=['POST'])
def handle_request():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    year = data.get('year')
    month = data.get('month')
    day = data.get('day')
    grib_file = data.get('grib_file')

    if None in (latitude, longitude, year, month, day, grib_file):
        return jsonify({"error": "Missing required parameters"}), 400

    max_temp = get_max_temperature(latitude, longitude, year, month, day, grib_file)
    if max_temp is not None:
        return jsonify({"max_temperature": max_temp}), 200
    else:
        return jsonify({"error": "Temperature data not found"}), 404

if __name__ == '__main__':
    app.run(debug=True)


