import pymysql
from flask import Flask, jsonify, request

app = Flask(__name__)


def connect_to_db():
    return pymysql.connect(host='localhost', user='root', password='password', db='temperature')


@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature_for_location():
    latitude = request.args.get('latitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    db = connect_to_db()
    cursor = db.cursor()
    query = "SELECT MAX(value) FROM temperature WHERE latitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s"
    cursor.execute(query, (latitude, year, month, day, grib_file))
    result = cursor.fetchall()
    db.close()

    return jsonify({"temperature": str(result[0][0])})


if __name__ == '__main__':
    app.run(debug=True)