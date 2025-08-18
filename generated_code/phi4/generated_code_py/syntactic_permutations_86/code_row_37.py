from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_database_connection():
    return mysql.connector.connect(
        host='localhost',
        user='your_username',  # Replace with your MySQL username
        password='your_password',  # Replace with your MySQL password
        database='your_database_name'  # Replace with your database name
    )

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not (latitude and longitude and year and month and day and grib_file):
        return jsonify({'error': 'Missing parameters'}), 400

    query = """
    SELECT temperature
    FROM weather_data
    WHERE latitude = %s AND longitude = %s AND year = %s 
      AND month = %s AND day = %s AND grib_file = %s;
    """

    try:
        connection = get_database_connection()
        cursor = connection.cursor()
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        
        result = cursor.fetchone()

        if result is None:
            return jsonify({'error': 'No data found'}), 404

        temperature = result[0]
        return jsonify({'temperature': temperature})

    except mysql.connector.Error as err:
        return jsonify({'error': str(err)}), 500
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == '__main__':
    app.run(debug=True)