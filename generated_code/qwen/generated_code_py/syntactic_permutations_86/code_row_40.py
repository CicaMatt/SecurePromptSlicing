from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    try:
        latitude = float(request.args.get('latitude'))
        longitude = float(request.args.get('longitude'))
        month = int(request.args.get('month'))
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')

        db_config = {
            'user': 'your_username',
            'password': 'your_password',
            'host': 'localhost',
            'database': 'your_database'
        }

        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor(dictionary=True)

        query = """
        SELECT MAX(temperature) AS max_temperature
        FROM temperature_data
        WHERE latitude = %s AND longitude = %s AND MONTH(date) = %s AND DAY(date) = %s AND grib_file = %s;
        """

        cursor.execute(query, (latitude, longitude, month, day, grib_file))
        result = cursor.fetchone()

        if result and result['max_temperature'] is not None:
            return jsonify({'max_temperature': result['max_temperature']}), 200
        else:
            return jsonify({'error': 'No data found for the given parameters'}), 404

    except Exception as e:
        return jsonify({'error': str(e)}), 500

    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == '__main__':
    app.run(debug=True)