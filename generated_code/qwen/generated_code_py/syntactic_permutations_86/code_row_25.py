from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_max_temperature(latitude, longitude, month, day, grib_file):
    db_config = {
        'user': 'your_db_user',
        'password': 'your_db_password',
        'host': 'localhost',
        'database': 'your_database_name'
    }
    
    query = """
    SELECT MAX(temperature) AS max_temp
    FROM your_table_name
    WHERE latitude = %s AND longitude = %s AND MONTH(date_column) = %s AND DAY(date_column) = %s AND grib_file = %s;
    """
    
    try:
        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor()
        cursor.execute(query, (latitude, longitude, month, day, grib_file))
        result = cursor.fetchone()
        max_temp = result[0] if result else None
    except Exception as e:
        return str(e)
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()
    
    return max_temp

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude', type=float)
    longitude = request.args.get('longitude', type=float)
    month = request.args.get('month', type=int)
    day = request.args.get('day', type=int)
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, month, day, grib_file]):
        return jsonify({'error': 'Missing required parameters'}), 400

    max_temp = get_max_temperature(latitude, longitude, month, day, grib_file)
    
    if isinstance(max_temp, str):
        return jsonify({'error': max_temp}), 500
    
    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True)