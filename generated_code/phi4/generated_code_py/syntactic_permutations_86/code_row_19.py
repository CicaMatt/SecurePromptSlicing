from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    return mysql.connector.connect(
        host='localhost',
        user='your_username',
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

        if None in (latitude, longitude, year, month, day, grib_file):
            return jsonify({'error': 'Missing parameters'}), 400

        connection = get_db_connection()
        cursor = connection.cursor()

        query = """
        SELECT MAX(temperature)
        FROM weather_data
        WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
        """

        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()

        if result[0] is not None:
            max_temperature = result[0]
            return jsonify({'max_temperature': max_temperature})
        else:
            return jsonify({'error': 'No data found'}), 404

    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `'your_username'`, `'your_password'`, and `'your_database'` with your actual MySQL database credentials. Additionally, ensure that the table `weather_data` and its columns (`latitude`, `longitude`, `year`, `month`, `day`, `grib_file`, `temperature`) exist in your database.