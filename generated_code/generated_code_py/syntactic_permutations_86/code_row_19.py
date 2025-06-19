import mysql.connector
from flask import Flask, jsonify, request, abort
app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_max_temp():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    # Connect to MySQL
    mysql = mysql.connector.connect(
        host='host',
        user='user',
        password='password',
        database='database'
    )
    cursor = mysql.cursor()

    # Execute query
    sql_query = f"SELECT max(temperature) FROM temperatures WHERE latitude={latitude} AND longitude={longitude} AND year={year} AND month={month} AND day={day} AND grib_file='{grib_file}'"
    cursor.execute(sql_query)
    result = cursor.fetchall()

    # Return response as JSON
    return jsonify([dict(zip(['max_temperature'], row)) for row in result])

# Run the app
if __name__ == '__main__':
    app.run(debug=True)