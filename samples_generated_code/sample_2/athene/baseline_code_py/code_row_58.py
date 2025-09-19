from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_max_temperature():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    year = int(request.args.get('year'))
    month = int(request.args.get('month'))
    day = int(request.args.get('day'))
    grib_file = request.args.get('grib_file')

    db = mysql.connector.connect(
        host="localhost",
        user="root",
        password="yourpassword",
        database="weather_data"
    )
    cursor = db.cursor()
    
    query = """
    SELECT MAX(temperature) 
    FROM weather_records 
    WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s
    """
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    
    result = cursor.fetchone()
    max_temperature = result[0] if result else None
    
    db.close()

    return jsonify({"max_temperature": max_temperature})

if __name__ == '__main__':
    app.run(debug=True)