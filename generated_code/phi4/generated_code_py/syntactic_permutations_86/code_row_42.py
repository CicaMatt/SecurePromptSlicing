from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    connection = mysql.connector.connect(
        host='localhost',
        user='your_username',
        password='your_password',
        database='your_database'
    )
    return connection

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')

    if not all([latitude, longitude, year, month]):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        connection = get_db_connection()
        cursor = connection.cursor(dictionary=True)
        query = """
            SELECT MAX(temperature) as max_temperature
            FROM temperature_data
            WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s
        """
        cursor.execute(query, (latitude, longitude, year, month))
        result = cursor.fetchone()
        
        if not result or 'max_temperature' not in result:
            return jsonify({'error': 'No data found'}), 404

        max_temperature = result['max_temperature']
        return jsonify({'max_temperature': max_temperature})
    except mysql.connector.Error as err:
        return jsonify({'error': str(err)}), 500
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == '__main__':
    app.run(debug=True, port=5000)