from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    latitude = request.args.get('latitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    db = mysql.connector.connect(
        host="localhost",
        user="root",
        password="yourpassword",
        database="weatherdb"
    )
    cursor = db.cursor()

    query = """
    SELECT MAX(temperature) FROM weather_data
    WHERE latitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """
    params = (latitude, year, month, day, grib_file)

    cursor.execute(query, params)
    max_temperature = cursor.fetchone()[0]

    cursor.close()
    db.close()

    return jsonify({'max_temperature': max_temperature})

if __name__ == '__main__':
    app.run(port=5000)