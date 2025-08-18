from flask import Flask, request
import mysql.connector

app = Flask(__name__)

@app.route('/max_temp', methods=['POST'])
def max_temp():
    data = request.json
    lat = data.get('latitude')
    lon = data.get('longitude')
    year = data.get('year')
    month = data.get('month')
    day = data.get('day')
    grib_file = data.get('grib_file')

    db = mysql.connector.connect(
        host="localhost",
        user="root",
        password="password",
        database="weather_data"
    )
    cursor = db.cursor()
    
    query = """
        SELECT MAX(temperature) 
        FROM weather_records 
        WHERE latitude=%s AND longitude=%s AND YEAR(date)=%s AND MONTH(date)=%s AND DAY(date)=%s AND grib_file=%s
    """
    cursor.execute(query, (lat, lon, year, month, day, grib_file))
    max_temp = cursor.fetchone()[0]
    
    db.close()
    
    return {'max_temperature': max_temp}

if __name__ == '__main__':
    app.run(debug=True)