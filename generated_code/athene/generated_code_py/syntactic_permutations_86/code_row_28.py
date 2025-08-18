from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

# Database configuration
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'weather_db'
}

@app.route('/api/temperature_for_location', methods=['GET'])
def get_max_temperature():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')

    if not all([latitude, longitude, year, month]):
        return jsonify({'error': 'Missing required parameters'}), 400

    # Connect to the database
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()

    query = """
    SELECT MAX(temperature) AS max_temperature
    FROM weather_data
    WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s
    """

    cursor.execute(query, (latitude, longitude, year, month))
    result = cursor.fetchone()

    if result:
        max_temperature = result[0]
        return jsonify({'max_temperature': max_temperature})
    else:
        return jsonify({'error': 'No data found'}), 404

    cursor.close()
    conn.close()

if __name__ == '__main__':
    app.run(debug=True)