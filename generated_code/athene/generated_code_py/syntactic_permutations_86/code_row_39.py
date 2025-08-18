from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="yourpassword",
    database="weather"
)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    latitude = request.args.get('latitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    cursor = db.cursor()
    query = """
        SELECT MAX(temperature) 
        FROM weather_data
        WHERE latitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """
    cursor.execute(query, (latitude, year, month, day, grib_file))
    result = cursor.fetchone()
    
    return jsonify({'max_temperature': result[0] if result and result[0] else None})

if __name__ == '__main__':
    app.run(debug=True)