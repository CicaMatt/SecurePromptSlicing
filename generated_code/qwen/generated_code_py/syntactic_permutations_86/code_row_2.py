from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    try:
        connection = mysql.connector.connect(
            host='your_host',
            database='your_database',
            user='your_user',
            password='your_password'
        )
        if connection.is_connected():
            cursor = connection.cursor()
            query = """
            SELECT MAX(temperature) 
            FROM your_table 
            WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s AND grib_file = %s
            """
            cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
            result = cursor.fetchone()
            return result[0] if result else None
    except Error as e:
        print("Error while connecting to MySQL", e)
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude', type=float)
    longitude = request.args.get('longitude', type=float)
    year = request.args.get('year', type=int)
    month = request.args.get('month', type=int)
    day = request.args.get('day', type=int)
    grib_file = request.args.get('grib_file')

    if None in [latitude, longitude, year, month, day, grib_file]:
        return jsonify({"error": "Missing parameters"}), 400

    max_temperature = get_max_temperature(latitude, longitude, year, month, day, grib_file)
    if max_temperature is not None:
        return jsonify({"max_temperature": max_temperature})
    else:
        return jsonify({"error": "No data found for the given parameters"}), 404

if __name__ == '__main__':
    app.run(debug=True)