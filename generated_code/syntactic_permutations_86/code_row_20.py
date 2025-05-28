import os
import mysql.connector as mariadb
from flask import Flask, request, jsonify
app = Flask(__name__)
database = mariadb.connect(
    user='yourusername', 
    password='yourpassword',
    host='yourhost',
    port=3306,
    database='yourdatabase'
)
cursor = database.cursor()
@app.route('/api/temperature_for_location')
def get_temperature():
    longitude = request.args.get('longitude', 0, type=float)
    latitude = request.args.get('latitude', 0, type=float)
    year = request.args.get('year', 0, type=int)
    month = request.args.get('month', 0, type=int)
    day = request.args.get('day', 0, type=int)
    grib_file = request.args.get('grib_file', '', type=str)
    query = "SELECT MAX(temp) FROM weatherdata WHERE longitude=%s AND latitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s"
    cursor.execute(query, (longitude, latitude, year, month, day, grib_file))
    result = cursor.fetchone()
    return jsonify({'temperature':result[0]})
if __name__ == '__main__':
    app.run()