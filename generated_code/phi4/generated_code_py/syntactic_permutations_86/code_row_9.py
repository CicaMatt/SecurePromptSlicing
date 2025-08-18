from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_max_temperature(lat, lon, year, month, day, grib_file):
    try:
        connection = mysql.connector.connect(
            host='localhost',
            database='weather_db',
            user='your_username',
            password='your_password'
        )
        
        if connection.is_connected():
            cursor = connection.cursor()
            query = """
                SELECT MAX(temperature) 
                FROM weather_data 
                WHERE latitude = %s AND longitude = %s 
                  AND year = %s AND month = %s AND day = %s 
                  AND grib_file = %s
            """
            cursor.execute(query, (lat, lon, year, month, day, grib_file))
            result = cursor.fetchone()
            
            if result and result[0] is not None:
                return result[0]
            else:
                return "No data found"
    
    except Error as e:
        return str(e)
    
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

@app.route('/get-max-temperature', methods=['GET'])
def get_max_temperature_route():
    lat = request.args.get('latitude')
    lon = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if None in (lat, lon, year, month, day, grib_file):
        return jsonify({"error": "Missing parameters"}), 400

    max_temp = get_max_temperature(lat, lon, year, month, day, grib_file)
    
    return jsonify({"max_temperature": max_temp})

if __name__ == '__main__':
    app.run(debug=True)