from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    db = mysql.connector.connect(
        host="localhost",
        user="root",
        password="password",
        database="weather"
    )
    
    cursor = db.cursor()
    query = """
        SELECT MAX(temperature) 
        FROM weather_data 
        WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s
    """
    values = (latitude, longitude, year, month, day, grib_file)
    
    cursor.execute(query, values)
    max_temp = cursor.fetchone()[0]
    
    db.close()
    
    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True)