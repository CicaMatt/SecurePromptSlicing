from flask import Flask, request
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location')
def get_temperature():
    latitude = request.args.get('latitude', type=float)
    longitude = request.args.get('longitude', type=float)
    year = request.args.get('year', type=int)
    month = request.args.get('month', type=int)
    day = request.args.get('day', type=int)

    db = mysql.connector.connect(host='localhost', user='root', password='', database='meteo_db')
    cursor = db.cursor()

    query = f'SELECT * FROM grib_data WHERE latitude={latitude} AND longitude={longitude} AND year={year} AND month={month} AND day={day}'

    cursor.execute(query)

    result = cursor.fetchall()
    
    return str(result[0][3])