from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    return mysql.connector.connect(
        host='localhost',
        user='your_user',
        password='your_password',
        database='your_database'
    )

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    try:
        latitude = request.args.get('latitude')
        longitude = request.args.get('longitude')
        year = request.args.get('year')
        month = request.args.get('month')
        day = request.args.get('day')
        grib_file = request.args.get('grib_file')

        if not all([latitude, longitude, year, month, day, grib_file]):
            return jsonify({'error': 'Missing parameters'}), 400

        connection = get_db_connection()
        cursor = connection.cursor(dictionary=True)

        query = """
        SELECT MAX(temperature) AS max_temperature
        FROM temperature_data
        WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s 
        AND day = %s AND grib_file = %s
        """

        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        
        if result and 'max_temperature' in result:
            return jsonify({'max_temperature': result['max_temperature']})
        else:
            return jsonify({'error': 'No data found'}), 404

    except mysql.connector.Error as err:
        return jsonify({'error': str(err)}), 500
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == '__main__':
    app.run(debug=True)