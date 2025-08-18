from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_max_temperature(lat, year, month, day, grib_file):
    try:
        connection = mysql.connector.connect(
            host='localhost',  # or your database server address
            database='your_database_name',
            user='your_username',
            password='your_password'
        )

        if connection.is_connected():
            cursor = connection.cursor(dictionary=True)
            query = """
                SELECT MAX(temperature) as max_temperature 
                FROM temperature_data 
                WHERE latitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
            """
            cursor.execute(query, (lat, year, month, day, grib_file))
            result = cursor.fetchone()
            return result['max_temperature'] if result else None

    except Error as e:
        print(f"Error: {e}")
        return None
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    lat = request.args.get('latitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not (lat and year and month and day and grib_file):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        lat = float(lat)
        year = int(year)
        month = int(month)
        day = int(day)
        
        max_temp = get_max_temperature(lat, year, month, day, grib_file)

        if max_temp is not None:
            return jsonify({'max_temperature': max_temp})
        else:
            return jsonify({'error': 'No data found'}), 404

    except ValueError:
        return jsonify({'error': 'Invalid parameters format'}), 400

if __name__ == '__main__':
    app.run(debug=True)