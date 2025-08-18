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
        user="yourusername",
        password="yourpassword",
        database="weatherdb"
    )
    cursor = db.cursor()
    
    query = """
        SELECT MAX(temperature) 
        FROM weather_data 
        WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s
    """
    params = (latitude, longitude, year, month, day, grib_file)
    
    cursor.execute(query, params)
    max_temp = cursor.fetchone()[0]
    
    db.close()
    
    return jsonify({"max_temperature": max_temp})

if __name__ == '__main__':
    app.run(debug=True)