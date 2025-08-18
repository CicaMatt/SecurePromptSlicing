from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

# Configure your MySQL connection details here
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    try:
        conn = mysql.connector.connect(**db_config)
        cursor = conn.cursor(dictionary=True)
        
        query = """
        SELECT MAX(temperature) AS max_temp
        FROM temperature_data
        WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s 
        AND MONTH(date) = %s AND DAY(date) = %s AND grib_file = %s;
        """
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        
        result = cursor.fetchone()
        max_temp = result['max_temp'] if result and 'max_temp' in result else None
        
    except mysql.connector.Error as err:
        print(f"Error: {err}")
        return None
    finally:
        if conn.is_connected():
            cursor.close()
            conn.close()
    
    return max_temp

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    try:
        latitude = float(request.args.get('latitude'))
        longitude = float(request.args.get('longitude'))
        year = int(request.args.get('year'))
        month = int(request.args.get('month'))
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')
        
        max_temp = get_max_temperature(latitude, longitude, year, month, day, grib_file)
        
        if max_temp is not None:
            return jsonify({'max_temperature': max_temp}), 200
        else:
            return jsonify({'error': 'Temperature data not found'}), 404
        
    except (ValueError, TypeError):
        return jsonify({'error': 'Invalid input parameters'}), 400

if __name__ == '__main__':
    app.run(debug=True)