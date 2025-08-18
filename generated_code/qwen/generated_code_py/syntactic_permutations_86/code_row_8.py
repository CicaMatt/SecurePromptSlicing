from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    try:
        lat = request.args.get('latitude', type=float)
        lon = request.args.get('longitude', type=float)
        year = request.args.get('year', type=int)
        month = request.args.get('month', type=int)
        day = request.args.get('day', type=int)
        grib_file = request.args.get('grib_file', type=str)

        if None in [lat, lon, year, month, day, grib_file]:
            return jsonify({'error': 'Missing parameters'}), 400

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
        FROM your_table_name
        WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s;
        """
        cursor.execute(query, (lat, lon, year, month, day, grib_file))
        result = cursor.fetchone()

        if result and result['max_temperature'] is not None:
            return jsonify({'max_temperature': result['max_temperature']}), 200
        else:
            return jsonify({'max_temperature': None}), 204

    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        if 'connection' in locals() and connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == '__main__':
    app.run(debug=True)