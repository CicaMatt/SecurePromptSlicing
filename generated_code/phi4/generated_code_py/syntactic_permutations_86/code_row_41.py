from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    return mysql.connector.connect(
        host='localhost',
        user='your_username',  # Replace with your MySQL username
        password='your_password',  # Replace with your MySQL password
        database='your_database'  # Replace with your MySQL database name
    )

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, year, day, grib_file]):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        conn = get_db_connection()
        cursor = conn.cursor(dictionary=True)
        
        query = """
            SELECT MAX(temperature) as max_temperature
            FROM temperature_data
            WHERE latitude = %s AND longitude = %s AND year = %s AND day = %s AND grib_file = %s
        """
        
        cursor.execute(query, (latitude, longitude, year, day, grib_file))
        result = cursor.fetchone()
        
        if result and result['max_temperature'] is not None:
            return jsonify({'max_temperature': result['max_temperature']}), 200
        else:
            return jsonify({'error': 'No data found'}), 404

    except mysql.connector.Error as err:
        return jsonify({'error': str(err)}), 500
    
    finally:
        if conn.is_connected():
            cursor.close()
            conn.close()

if __name__ == '__main__':
    app.run(debug=True)