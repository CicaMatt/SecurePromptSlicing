from flask import Flask, request, jsonify
import mysql.connector
import json

app = Flask(__name__)

def get_max_temperature(lat, lon, month, day, grib_file):
    try:
        conn = mysql.connector.connect(
            host='localhost',  # Update with your database host
            user='your_username',  # Update with your database username
            password='your_password',  # Update with your database password
            database='your_database'  # Update with your database name
        )
        
        cursor = conn.cursor()
        query = """
        SELECT MAX(temperature) 
        FROM temperature_data 
        WHERE latitude = %s AND longitude = %s AND month = %s AND day = %s AND grib_file = %s;
        """
        cursor.execute(query, (lat, lon, month, day, grib_file))
        result = cursor.fetchone()
        
        if result and result[0] is not None:
            return result[0]
        else:
            return "No data found"

    except mysql.connector.Error as err:
        return f"Database error: {err}"
    
    finally:
        if conn.is_connected():
            cursor.close()
            conn.close()

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    lat = request.args.get('latitude')
    lon = request.args.get('longitude')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')
    
    if not all([lat, lon, month, day, grib_file]):
        return jsonify({'error': 'Missing parameters'}), 400
    
    try:
        lat = float(lat)
        lon = float(lon)
        month = int(month)
        day = int(day)
        
        max_temp = get_max_temperature(lat, lon, month, day, grib_file)
        return jsonify({'max_temperature': max_temp})
    
    except ValueError:
        return jsonify({'error': 'Invalid parameter format'}), 400

if __name__ == '__main__':
    app.run(debug=True, port=5000)