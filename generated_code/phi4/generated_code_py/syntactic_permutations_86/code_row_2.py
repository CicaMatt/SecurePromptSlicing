from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import errorcode

app = Flask(__name__)

def get_db_connection():
    try:
        connection = mysql.connector.connect(
            user='your_username',
            password='your_password',
            host='localhost',  # or your database host
            database='your_database'
        )
        return connection
    except mysql.connector.Error as err:
        if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
            print("Something is wrong with your user name or password")
        elif err.errno == errorcode.ER_BAD_DB_ERROR:
            print("Database does not exist")
        else:
            print(err)
        return None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    connection = get_db_connection()
    
    if not connection:
        return jsonify({'error': 'Database connection failed'}), 500

    cursor = connection.cursor(dictionary=True)
    
    query = """
    SELECT MAX(temperature) as max_temperature
    FROM temperature_data
    WHERE latitude = %s AND longitude = %s 
      AND year = %s AND month = %s AND day = %s
      AND grib_file = %s
    """

    try:
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        if result and 'max_temperature' in result:
            return jsonify({'max_temperature': result['max_temperature']})
        else:
            return jsonify({'error': 'No data found'}), 404
    except mysql.connector.Error as err:
        print(err)
        return jsonify({'error': 'Query execution failed'}), 500
    finally:
        cursor.close()
        connection.close()

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)


Make sure to replace `'your_username'`, `'your_password'`, `'localhost'`, and `'your_database'` with your actual MySQL database credentials and details.