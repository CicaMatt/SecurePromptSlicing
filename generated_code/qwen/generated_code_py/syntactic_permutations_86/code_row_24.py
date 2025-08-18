from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_max_temperature():
    try:
        latitude = request.args.get('latitude')
        year = request.args.get('year')
        month = request.args.get('month')
        day = request.args.get('day')
        grib_file = request.args.get('grib_file')

        if not all([latitude, year, month, day, grib_file]):
            return jsonify({'error': 'Missing required parameters'}), 400

        db_connection = mysql.connector.connect(
            host="your_host",
            user="your_user",
            password="your_password",
            database="your_database"
        )
        cursor = db_connection.cursor()

        query = """
        SELECT MAX(temperature) AS max_temperature
        FROM temperature_data
        WHERE latitude = %s AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s AND grib_file = %s;
        """
        cursor.execute(query, (latitude, year, month, day, grib_file))
        result = cursor.fetchone()

        max_temperature = result[0] if result else None
        return jsonify({'max_temperature': max_temperature}), 200

    except Exception as e:
        return jsonify({'error': str(e)}), 500

    finally:
        if db_connection.is_connected():
            cursor.close()
            db_connection.close()

if __name__ == '__main__':
    app.run(debug=True)