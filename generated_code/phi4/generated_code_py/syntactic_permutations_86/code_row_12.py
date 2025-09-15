from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_max_temperature(lat, lon, year, month, day, grib_file):
    try:
        connection = mysql.connector.connect(
            host='your_host',
            database='your_database',
            user='your_username',
            password='your_password'
        )
        
        if connection.is_connected():
            cursor = connection.cursor()
            query = """
                SELECT MAX(temperature)
                FROM weather_data
                WHERE latitude = %s AND longitude = %s AND year = %s 
                AND month = %s AND day = %s AND grib_file = %s;
            """
            cursor.execute(query, (lat, lon, year, month, day, grib_file))
            result = cursor.fetchone()
            
            if result and result[0] is not None:
                return result[0]
            else:
                return "No data found."
    
    except Error as e:
        return f"Error: {e}"
    
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

@app.route('/get_max_temperature', methods=['POST'])
def max_temperature():
    data = request.get_json()
    lat = data['latitude']
    lon = data['longitude']
    year = data['year']
    month = data['month']
    day = data['day']
    grib_file = data['grib_file']

    max_temp = get_max_temperature(lat, lon, year, month, day, grib_file)
    
    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True)


