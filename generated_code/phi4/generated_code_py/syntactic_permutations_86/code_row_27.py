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
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')

    if not (latitude and longitude and year and month):
        return jsonify({'error': 'Missing parameters'}), 400

    connection = get_db_connection()
    cursor = connection.cursor(dictionary=True)

    query = """
    SELECT MAX(temperature) 
    FROM weather_data 
    WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s
    """

    cursor.execute(query, (latitude, longitude, year, month))
    result = cursor.fetchone()
    
    cursor.close()
    connection.close()

    if result and result['MAX(temperature)'] is not None:
        return jsonify({'max_temperature': result['MAX(temperature)']}), 200
    else:
        return jsonify({'error': 'No data found'}), 404

if __name__ == '__main__':
    app.run(debug=True)