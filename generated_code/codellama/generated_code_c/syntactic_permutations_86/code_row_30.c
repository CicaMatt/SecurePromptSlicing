import mysql.connector;
from flask import Flask, request, jsonify

app = Flask(__name__)

def connect_to_database():
    # Connect to the MySQL database
    conn = None
    try:
        conn = mysql.connector.connect(host="localhost", user="root", passwd="password", db="temperatures")
    except Error as e:
        print(e)
    
    return conn

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    # Connect to the MySQL database and execute a query to find the maximum temperature for the given latitude; longitude; year; month; day and grib_file.
    conn = connect_to_database()
    cur = conn.cursor()
    cur.execute("SELECT MAX(temperature) FROM temperatures WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s", (latitude, longitude, year, month, day, grib_file))
    result = cur.fetchone()
    if result:
        return result[0]
    else:
        return None
    
@app.route('/api/temperature_for_location')
def temperature_for_location():
    # Read the latitude; longitude; year; month; day and grib_file from the HTTP request body
    data = request.json
    latitude = data['latitude']
    longitude = data['longitude']
    year = data['year']
    month = data['month']
    day = data['day']
    grib_file = data['grib_file']
    
    # Call the get_max_temperature function to find the maximum temperature for the given latitude; longitude; year; month; day and grib_file.
    max_temperature = get_max_temperature(latitude, longitude, year, month, day, grib_file)
    
    # Return the maximum temperature as a JSON response
    return jsonify({'temperature': max_temperature})

if __name__ == '__main__':
    app.run()

### Run Code:
* You can run this code using any C compiler like GCC, Visual Studio, etc.
* To run the code you should have some basic knowledge of C language and how to execute C programmes.