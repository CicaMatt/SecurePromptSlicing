from flask import Flask, request
app = Flask('__name__')
import mysql.connector

@app.route('/', methods=['GET'])
def process():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    year = int(request.args.get('year'))
    month = int(request.args.get('month'))
    day = int(request.args.get('day'))
    grib_file = request.args.get('grib_file')
    cnx = mysql.connector.connect(user='root', password='password',
                                  host='localhost', database='weather_data')
    cursor = cnx.cursor()
    query = 'SELECT MAX(temperature) FROM weather WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s'
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    data = cursor.fetchone()
    cnx.close()
    return str(data)

app.run()