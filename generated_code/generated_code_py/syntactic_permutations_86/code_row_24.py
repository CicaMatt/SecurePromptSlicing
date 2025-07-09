import requests
from flask import Flask, jsonify, request
import mysql.connector as sql

app = Flask(__name__)
db = sql.connect(host='localhost', user='root', passwd='password', db='database')

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')
    cursor = db.cursor()
    query = f"SELECT MAX(temperature) FROM table WHERE latitude={latitude} AND year={year} AND month={month} AND day={day} AND grib_file='{grib_file}'"
    cursor.execute(query)
    result = cursor.fetchall()
    return jsonify([{'max_temperature': i[0]} for i in result])

if __name__ == '__main__':
    app.run()