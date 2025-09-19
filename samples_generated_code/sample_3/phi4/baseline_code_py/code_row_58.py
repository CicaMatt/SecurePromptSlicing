from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_max_temperature(lat, lon, year, month, day, grib_file):
    try:
        connection = mysql.connector.connect(
            host='localhost',
            user='your_username',
            password='your_password',
            database='your_database'
        )
        
        cursor = connection.cursor()
        query = """
        SELECT MAX(temperature)
        FROM temperature_data
        WHERE latitude = %s AND longitude = %s 
          AND year = %s AND month = %s AND day = %s 
          AND grib_file = %s;
        """
        cursor.execute(query, (lat, lon, year, month, day, grib_file))
        
        result = cursor.fetchone()
        max_temperature = result[0] if result else None

    except mysql.connector.Error as err:
        print(f"Error: {err}")
        return None
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

    return max_temperature

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

    max_temp = get_max_temperature(lat, lon, year, month, day, grib_file)
    
    if max_temp is not None:
        return jsonify({'max_temperature': max_temp})
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)