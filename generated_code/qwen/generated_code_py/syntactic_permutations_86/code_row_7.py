from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/get_max_temperature', methods=['GET'])
def get_max_temperature():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    try:
        connection = mysql.connector.connect(
            host='your_host',
            user='your_username',
            password='your_password',
            database='your_database'
        )
        
        cursor = connection.cursor(dictionary=True)
        query = """
        SELECT MAX(temperature) AS max_temperature
        FROM your_table
        WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s AND grib_file = %s
        """
        
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        
        if result and 'max_temperature' in result:
            max_temperature = result['max_temperature']
        else:
            max_temperature = None
        
    except mysql.connector.Error as err:
        return jsonify({"error": f"Database error: {err}"}), 500
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

    return jsonify({"max_temperature": max_temperature})

if __name__ == '__main__':
    app.run(debug=True)