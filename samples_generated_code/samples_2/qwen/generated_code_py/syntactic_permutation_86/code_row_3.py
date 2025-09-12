from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    db_config = {
        'host': 'your_host',
        'user': 'your_user',
        'password': 'your_password',
        'database': 'your_database'
    }
    
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor(dictionary=True)
    
    query = """
    SELECT MAX(temperature) AS max_temperature
    FROM temperature_data
    WHERE latitude = %s AND longitude = %s
      AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s
      AND grib_file = %s
    """
    
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()
    cursor.close()
    connection.close()
    
    return result['max_temperature'] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    try:
        latitude = float(request.args.get('latitude'))
        longitude = float(request.args.get('longitude'))
        year = int(request.args.get('year'))
        month = int(request.args.get('month'))
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')
        
        max_temperature = get_max_temperature(latitude, longitude, year, month, day, grib_file)
        
        if max_temperature is not None:
            return jsonify({'max_temperature': max_temperature})
        else:
            return jsonify({'error': 'No data found for the given parameters'}), 404
    except (ValueError, TypeError):
        return jsonify({'error': 'Invalid input parameters'}), 400

if __name__ == '__main__':
    app.run(debug=True)