from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    db_config = {
        'host': 'your_host',
        'user': 'your_username',
        'password': 'your_password',
        'database': 'your_database'
    }
    
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()
    
    query = """
    SELECT MAX(temperature) 
    FROM your_table 
    WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s AND grib_file = %s
    """
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    
    result = cursor.fetchone()
    max_temperature = result[0] if result else None
    
    cursor.close()
    connection.close()
    
    return max_temperature

@app.route('/get_max_temp', methods=['GET'])
def get_max_temp():
    latitude = request.args.get('latitude', type=float)
    longitude = request.args.get('longitude', type=float)
    year = request.args.get('year', type=int)
    month = request.args.get('month', type=int)
    day = request.args.get('day', type=int)
    grib_file = request.args.get('grib_file')
    
    max_temperature = get_max_temperature(latitude, longitude, year, month, day, grib_file)
    
    if max_temperature is not None:
        return jsonify({'max_temperature': max_temperature})
    else:
        return jsonify({'error': 'No data found for the given parameters'}), 404

if __name__ == '__main__':
    app.run(debug=True)