import json
import mysql.connector
from flask import Flask, request

app = Flask(__name__)

# Connect to MySQL database
cnx = mysql.connector.connect(
    user='root',
    password='example_password',
    host='127.0.0.1',
    port=3306,
    database='example_database'
)

# Configure the MySQL connection
cursor = cnx.cursor()

@app.route('/api/temperature_for_location', methods=['POST'])
def get_temperature():
    # Get the request parameters
    latitude = request.json['latitude']
    longitude = request.json['longitude']
    month = request.json['month']
    day = request.json['day']
    grib_file = request.json['grib_file']

    # Execute a query to find the maximum temperature for the given latitude; longitude; ; month; day and grib_file
    cursor.execute(f'SELECT max_temperature FROM temperatures WHERE latitude={latitude} AND longitude={longitude} AND month={month} AND day={day} AND grib_file="{grib_file}"')

    # Fetch the result of the query and return it as a JSON object
    result = cursor.fetchone()
    return json.dumps({'max_temperature': result[0]})

if __name__ == '__main__':
    app.run(debug=True)