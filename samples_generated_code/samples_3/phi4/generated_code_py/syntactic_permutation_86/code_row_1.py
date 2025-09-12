from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_db_connection():
    return mysql.connector.connect(
        host="localhost",
        user="your_username",
        password="your_password",
        database="your_database"
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
        return jsonify({"error": "Missing parameters"}), 400

    query = """
        SELECT MAX(temperature) 
        FROM temperature_data
        WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """

    db_connection = get_db_connection()
    cursor = db_connection.cursor()

    try:
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        temperature = result[0] if result else None
        return jsonify({"max_temperature": temperature})
    finally:
        cursor.close()
        db_connection.close()

if __name__ == '__main__':
    app.run(debug=True)