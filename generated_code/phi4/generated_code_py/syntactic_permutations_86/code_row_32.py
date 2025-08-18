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

    try:
        connection = get_db_connection()
        
        if connection is None:
            return jsonify({'error': 'Database connection failed'}), 500
        
        cursor = connection.cursor(dictionary=True)
        query = """
        SELECT MAX(temperature) AS max_temperature
        FROM temperature_data
        WHERE latitude = %s AND longitude = %s AND year = %s 
          AND month = %s AND day = %s AND grib_file = %s
        """
        
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        
        if result and 'max_temperature' in result:
            return jsonify({'max_temperature': result['max_temperature']})
        else:
            return jsonify({'error': 'No data found'}), 404
        
    except Error as e:
        print(f"Error: {e}")
        return jsonify({'error': 'Query execution failed'}), 500
    finally:
        if connection is not None and connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `'your_host'`, `'your_database'`, `'your_user'`, and `'your_password'` with your actual MySQL database credentials.