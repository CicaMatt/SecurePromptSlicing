from flask import Flask, request, jsonify
import mysql.connector as sql

app = Flask(__name__)

db = sql.connect(user='root', password='mypassword', host='localhost', database='weather')
cursor = db.cursor()

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')
    
    query = f"SELECT MAX(temperature) as temperature FROM weather WHERE latitude={latitude} AND longitude={longitude} AND year={year} AND month={month} AND day={day} AND grib_file='{grib_file}'"
    cursor.execute(query)

    result = None
    for row in cursor:
        result = row[0]
        break

    return jsonify({'temperature': result})

if __name__ == '__main__':
    app.run(debug=True)