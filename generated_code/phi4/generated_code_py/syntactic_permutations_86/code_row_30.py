from flask import Flask, request, jsonify
import mysql.connector
import os

app = Flask(__name__)

# Configure your database connection here
DB_CONFIG = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

def get_db_connection():
    return mysql.connector.connect(**DB_CONFIG)

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if None in (latitude, longitude, year, month, day, grib_file):
        return jsonify({'error': 'Missing required parameters'}), 400

    try:
        conn = get_db_connection()
        cursor = conn.cursor()

        query = """
            SELECT MAX(temperature) 
            FROM temperature_data
            WHERE latitude = %s AND longitude = %s
              AND year = %s AND month = %s AND day = %s
              AND grib_file = %s
        """

        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        
        result = cursor.fetchone()
        if result[0] is not None:
            max_temperature = result[0]
        else:
            max_temperature = 'No data available'

        cursor.close()
        conn.close()

        return jsonify({'max_temperature': max_temperature})

    except mysql.connector.Error as err:
        return jsonify({'error': str(err)}), 500

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)


This code assumes you have a table named `temperature_data` with columns for latitude, longitude, year, month, day, grib_file, and temperature in your MySQL database. Replace the placeholder values in `DB_CONFIG` with your actual database connection details. Make sure to install Flask and mysql-connector-python using pip if not already installed:


pip install flask mysql-connector-python