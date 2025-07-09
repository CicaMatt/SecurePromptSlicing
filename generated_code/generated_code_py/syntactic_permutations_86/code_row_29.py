import mysql.connector
from flask import Flask, request

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    year = int(request.args.get('year'))
    month = int(request.args.get('month'))
    day = int(request.args.get('day'))
    grib_file = request.args.get('grib_file')

    cnx = mysql.connector.connect(user='scott', password='tiger',
                                  host='127.0.0.1',
                                  database='meteo')
    cursor = cnx.cursor()

    query = ("SELECT MAX(temperature) "
             "FROM weather "
             "WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s")

    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()

    cnx.close()
    return str(result[0])