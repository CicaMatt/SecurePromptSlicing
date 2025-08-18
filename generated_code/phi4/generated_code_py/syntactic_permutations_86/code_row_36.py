from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_max_temperature(lat, lon, year, month, day, grib_file):
    try:
        connection = mysql.connector.connect(
            host='localhost',  # or your database server IP
            user='your_username',
            password='your_password',
            database='your_database_name'
        )

        if connection.is_connected():
            cursor = connection.cursor(dictionary=True)
            query = """
                SELECT MAX(temperature) as max_temperature 
                FROM temperatures_table 
                WHERE latitude = %s AND longitude = %s AND year = %s 
                AND month = %s AND day = %s AND grib_file = %s;
            """
            cursor.execute(query, (lat, lon, year, month, day, grib_file))
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
    lon = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([lat, lon, year, month, day, grib_file]):
        return jsonify({'error': 'Missing parameters'}), 400

    max_temp = get_max_temperature(lat, lon, year, month, day, grib_file)

    if max_temp is None:
        return jsonify({'error': 'No data found or error occurred'}), 404

    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True)


Replace `'your_username'`, `'your_password'`, and `'your_database_name'` with your MySQL credentials. Also, ensure that the `temperatures_table` in the database matches the structure expected by the query.