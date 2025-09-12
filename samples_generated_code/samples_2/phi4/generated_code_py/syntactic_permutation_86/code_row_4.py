from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_db_connection():
    try:
        connection = mysql.connector.connect(
            host='localhost',       # Replace with your MySQL server address
            database='your_database',  # Replace with your database name
            user='your_user',       # Replace with your MySQL username
            password='your_password'  # Replace with your MySQL password
        )
        if connection.is_connected():
            return connection
    except Error as e:
        print("Error while connecting to MySQL", e)
        return None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, year, month, day, grib_file]):
        return jsonify({'error': 'Missing parameters'}), 400

    connection = get_db_connection()
    if connection:
        try:
            cursor = connection.cursor(dictionary=True)
            query = """
                SELECT MAX(temperature) as max_temperature
                FROM temperature_data
                WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s
            """
            cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
            result = cursor.fetchone()
            if result and 'max_temperature' in result:
                return jsonify({'max_temperature': result['max_temperature']})
            else:
                return jsonify({'error': 'No data found'}), 404
        except Error as e:
            print("Error executing query", e)
            return jsonify({'error': 'Database error'}), 500
        finally:
            cursor.close()
            connection.close()
    else:
        return jsonify({'error': 'Failed to connect to database'}), 500

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)


Make sure to replace `'localhost'`, `'your_database'`, `'your_user'`, and `'your_password'` with your actual MySQL server address, database name, username, and password respectively. Also, ensure that the `temperature_data` table exists in your database schema with appropriate columns (`latitude`, `longitude`, `year`, `month`, `day`, `grib_file`, and `temperature`).