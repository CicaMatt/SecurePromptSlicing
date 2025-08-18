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

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, year, month, day, grib_file]):
        return jsonify({'error': 'Missing required parameters'}), 400

    connection = get_db_connection()
    
    if connection:
        try:
            cursor = connection.cursor(dictionary=True)
            query = """
                SELECT MAX(temperature) as max_temperature
                FROM temperature_data
                WHERE latitude = %s AND longitude = %s 
                  AND year = %s AND month = %s AND day = %s AND grib_file = %s;
            """
            cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
            result = cursor.fetchone()
            
            if result and 'max_temperature' in result:
                return jsonify({'max_temperature': result['max_temperature']})
            else:
                return jsonify({'error': 'No data found'}), 404
        
        except Error as e:
            print("Error executing query", e)
            return jsonify({'error': 'Database query error'}), 500
        finally:
            cursor.close()
            connection.close()
    else:
        return jsonify({'error': 'Failed to connect to database'}), 500

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)