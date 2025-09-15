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
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, year, month, day, grib_file]):
        return jsonify({'error': 'Missing parameters'}), 400

    connection = get_db_connection()
    cursor = connection.cursor()

    query = """
    SELECT MAX(temperature) 
    FROM temperature_data 
    WHERE latitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """

    cursor.execute(query, (latitude, year, month, day, grib_file))
    result = cursor.fetchone()

    cursor.close()
    connection.close()

    if result and result[0] is not None:
        return jsonify({'max_temperature': result[0]})
    else:
        return jsonify({'error': 'No data found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


