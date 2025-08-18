from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_max_temperature():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, year, month, day, grib_file]):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        connection = mysql.connector.connect(
            host='your_host',
            user='your_username',
            password='your_password',
            database='your_database'
        )
        cursor = connection.cursor()
        
        query = """
        SELECT MAX(temperature) AS max_temperature
        FROM your_table_name
        WHERE latitude = %s AND longitude = %s AND YEAR(date_column) = %s 
        AND MONTH(date_column) = %s AND DAY(date_column) = %s AND grib_file = %s;
        """
        
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        
        if result and result[0] is not None:
            return jsonify({'max_temperature': result[0]})
        else:
            return jsonify({'max_temperature': None})
    
    except mysql.connector.Error as err:
        return jsonify({'error': str(err)}), 500
    
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == '__main__':
    app.run(debug=True)