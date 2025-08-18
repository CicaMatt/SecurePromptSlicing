from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_max_temperature(lat, lon, year, month, day, grib_file):
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
                FROM temperature_data 
                WHERE latitude = %s AND longitude = %s AND year = %s 
                  AND month = %s AND day = %s AND grib_file = %s
            """
            cursor.execute(query, (lat, lon, year, month, day, grib_file))
            
            result = cursor.fetchone()
            if result and result[0] is not None:
                return result[0]
            else:
                return "No data found"
    
    except Error as e:
        return f"Error: {str(e)}"
    
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

    max_temperature = get_max_temperature(lat, lon, year, month, day, grib_file)
    return jsonify({'max_temperature': max_temperature})

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `'your_host'`, `'your_database'`, `'your_user'`, and `'your_password'` with your actual MySQL database credentials.