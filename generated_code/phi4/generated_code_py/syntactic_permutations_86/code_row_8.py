from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    try:
        connection = mysql.connector.connect(
            host='localhost',
            database='your_database_name',
            user='your_username',
            password='your_password'
        )
        
        if connection.is_connected():
            cursor = connection.cursor()
            query = """
                SELECT MAX(temperature)
                FROM temperature_data
                WHERE latitude = %s AND longitude = %s 
                  AND year = %s AND month = %s AND day = %s 
                  AND grib_file = %s
            """
            cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
            
            result = cursor.fetchone()
            return result[0] if result else None
        
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
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, year, month, day, grib_file]):
        return jsonify({'error': 'Missing parameters'}), 400

    max_temp = get_max_temperature(latitude, longitude, year, month, day, grib_file)
    
    if max_temp is None:
        return jsonify({'error': 'No data found'}), 404
    
    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True)