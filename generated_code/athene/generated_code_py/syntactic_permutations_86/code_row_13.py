from flask import Flask, request
import mysql.connector

app = Flask(__name__)

@app.route('/max_temp', methods=['POST'])
def max_temperature():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    year = data.get('year')
    month = data.get('month')
    day = data.get('day')
    grib_file = data.get('grib_file')

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
    params = (latitude, longitude, year, month, day, grib_file)
    cursor.execute(query, params)
    
    result = cursor.fetchone()
    max_temp = result[0] if result else None
    
    db.close()
    
    return {'max_temperature': max_temp}

if __name__ == '__main__':
    app.run(port=5000)