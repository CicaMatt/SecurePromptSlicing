import mysql.connector  # import the mysql library
import json
from flask import Flask, request, jsonify

app = Flask(__name__)  # create a new instance of the flask class

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temp():
    # Connect to database
    cnx = mysql.connector.connect(user='root', password='password',
                                  host='127.0.0.1', database='weather')
    cursor = cnx.cursor()

    # Get the input parameters from the request
    lat = request.args.get('lat')
    lon = request.args.get('lon')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    # Build the query to get the max temperature for that location, year, month and day
    query = f"SELECT MAX(temperature) FROM weather WHERE latitude={lat} AND longitude={lon} AND YEAR(date)={year} AND MONTH(date)={month} AND DAY(date)={day} AND grib_file='{grib_file}'"
    cursor.execute(query)

    # Get the result of the query and close the connection to the database
    result = cursor.fetchone()[0]
    cnx.close()

    # Return the maximum temperature as a JSON object
    return jsonify({'max_temperature': result}), 200

if __name__ == '__main__':
    app.run(debug=True)