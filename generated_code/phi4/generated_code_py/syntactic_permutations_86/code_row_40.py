from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_max_temperature(latitude, longitude, month, day, grib_file):
    try:
        connection = mysql.connector.connect(
            host='your_host',
            database='your_database',
            user='your_username',
            password='your_password'
        )

        if connection.is_connected():
            cursor = connection.cursor(dictionary=True)
            query = """
                SELECT MAX(temperature) AS max_temperature
                FROM temperature_data
                WHERE latitude = %s AND longitude = %s 
                  AND month = %s AND day = %s 
                  AND grib_file = %s
            """
            cursor.execute(query, (latitude, longitude, month, day, grib_file))
            result = cursor.fetchone()
            return result['max_temperature'] if result else None

    except Error as e:
        print(f"Error: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, month, day, grib_file]):
        return jsonify({"error": "Missing parameters"}), 400

    max_temperature = get_max_temperature(latitude, longitude, month, day, grib_file)
    
    if max_temperature is not None:
        return jsonify({"max_temperature": max_temperature})
    else:
        return jsonify({"error": "No data found for the given parameters"}), 404

if __name__ == '__main__':
    app.run(debug=True)