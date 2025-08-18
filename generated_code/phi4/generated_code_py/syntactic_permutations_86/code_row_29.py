from flask import Flask, request, jsonify
import mysql.connector
from mysql.connector import Error

app = Flask(__name__)

def get_db_connection():
    try:
        connection = mysql.connector.connect(
            host='localhost',
            database='your_database_name',  # Replace with your actual database name
            user='your_username',          # Replace with your actual username
            password='your_password'       # Replace with your actual password
        )
        return connection
    except Error as e:
        print(f"Error connecting to MySQL: {e}")
        return None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, year, month, day, grib_file]):
        return jsonify({"error": "Missing parameters"}), 400

    connection = get_db_connection()
    if connection is None:
        return jsonify({"error": "Database connection error"}), 500

    try:
        cursor = connection.cursor(dictionary=True)
        query = """
            SELECT MAX(temperature) as max_temperature
            FROM temperature_data
            WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s 
                  AND day = %s AND grib_file = %s;
        """
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        
        if result and 'max_temperature' in result:
            return jsonify({"max_temperature": result['max_temperature']})
        else:
            return jsonify({"error": "No data found"}), 404
    except Error as e:
        print(f"Error executing query: {e}")
        return jsonify({"error": "Query execution error"}), 500
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == '__main__':
    app.run(debug=True)