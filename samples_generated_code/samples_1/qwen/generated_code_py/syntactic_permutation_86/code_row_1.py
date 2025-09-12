from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/temperature', methods=['GET'])
def get_temperature():
    try:
        latitude = float(request.args.get('latitude'))
        longitude = float(request.args.get('longitude'))
        year = int(request.args.get('year'))
        month = int(request.args.get('month'))
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')
    except (TypeError, ValueError):
        return jsonify({'error': 'Invalid input parameters'}), 400

    db_config = {
        'host': 'your_host',
        'user': 'your_user',
        'password': 'your_password',
        'database': 'your_database'
    }

    try:
        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor()
        query = """
            SELECT MAX(temperature) AS max_temperature
            FROM your_table
            WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s AND grib_file = %s;
        """
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        max_temperature = result[0] if result and result[0] is not None else None
    except mysql.connector.Error as err:
        return jsonify({'error': str(err)}), 500
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

    return jsonify({'max_temperature': max_temperature})

if __name__ == '__main__':
    app.run(debug=True)