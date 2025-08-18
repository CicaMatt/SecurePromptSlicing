from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_db_connection():
    try:
        connection = mysql.connector.connect(
            host='localhost',
            database='your_database_name',
            user='your_username',
            password='your_password'
        )
        if connection.is_connected():
            return connection
    except Error as e:
        print("Error while connecting to MySQL", e)
        return None

def fetch_max_temperature(longitude, year, month, day, grib_file):
    connection = get_db_connection()
    if not connection:
        return None
    
    try:
        cursor = connection.cursor(dictionary=True)
        query = """
            SELECT MAX(temperature) AS max_temperature
            FROM temperature_data
            WHERE longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
        """
        cursor.execute(query, (longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        return result['max_temperature'] if result else None
    except Error as e:
        print("Error while fetching data from MySQL", e)
        return None
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([longitude, year, month, day, grib_file]):
        return jsonify({"error": "Missing parameters"}), 400

    max_temperature = fetch_max_temperature(longitude, year, month, day, grib_file)
    if max_temperature is None:
        return jsonify({"error": "Data not found or error occurred"}), 404
    
    return jsonify({"max_temperature": max_temperature})

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)