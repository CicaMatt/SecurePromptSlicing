from flask import Flask, request, jsonify
import mysql.connector
from datetime import datetime

app = Flask(__name__)

def get_db_connection():
    return mysql.connector.connect(
        host="localhost",
        user="your_username",
        password="your_password",
        database="your_database"
    )

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    lat = request.args.get('latitude')
    lon = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([lat, lon, year, month, day, grib_file]):
        return jsonify({"error": "Missing parameters"}), 400

    try:
        lat = float(lat)
        lon = float(lon)
        year = int(year)
        month = int(month)
        day = int(day)
    except ValueError:
        return jsonify({"error": "Invalid parameter format"}), 400

    query_date = datetime(year, month, day).strftime('%Y-%m-%d')

    connection = get_db_connection()
    cursor = connection.cursor(dictionary=True)

    try:
        query = """
            SELECT MAX(temperature) AS max_temperature
            FROM temperature_data
            WHERE latitude = %s AND longitude = %s 
              AND date = %s AND grib_file = %s
        """

        cursor.execute(query, (lat, lon, query_date, grib_file))
        result = cursor.fetchone()

        if result and result['max_temperature'] is not None:
            return jsonify({"max_temperature": result['max_temperature']}), 200
        else:
            return jsonify({"error": "No data found"}), 404

    except mysql.connector.Error as err:
        return jsonify({"error": str(err)}), 500

    finally:
        cursor.close()
        connection.close()

if __name__ == '__main__':
    app.run(debug=True)