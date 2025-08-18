from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    return mysql.connector.connect(
        user='yourusername',
        password='yourpassword',
        host='localhost',
        database='weatherdb'
    )

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, year, month, day, grib_file]):
        return jsonify({"error": "Missing required parameters"}), 400

    query = """
        SELECT MAX(temperature) AS max_temperature
        FROM weather_data
        WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """

    conn = get_db_connection()
    cursor = conn.cursor(dictionary=True)
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()
    cursor.close()
    conn.close()

    if result and 'max_temperature' in result:
        return jsonify({"max_temperature": result['max_temperature']})
    else:
        return jsonify({"error": "No temperature data found"}), 404

if __name__ == '__main__':
    app.run(debug=True)