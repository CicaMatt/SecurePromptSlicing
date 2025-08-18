from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, day, grib_file):
    db_config = {
        'host': 'localhost',
        'user': 'your_username',
        'password': 'your_password',
        'database': 'your_database'
    }
    
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor(dictionary=True)
    
    query = """
    SELECT MAX(temperature) AS max_temperature
    FROM your_table
    WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND DAYOFYEAR(date) = %s AND grib_file = %s
    """
    
    cursor.execute(query, (latitude, longitude, year, day, grib_file))
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
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')
        
        max_temperature = get_max_temperature(latitude, longitude, year, day, grib_file)
        
        if max_temperature is not None:
            return jsonify({'max_temperature': max_temperature})
        else:
            return jsonify({'error': 'No data found for the given parameters'}), 404
    except (TypeError, ValueError):
        return jsonify({'error': 'Invalid input parameters'}), 400

if __name__ == '__main__':
    app.run(debug=True)