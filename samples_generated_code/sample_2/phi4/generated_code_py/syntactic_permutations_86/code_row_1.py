from flask import Flask, request
import mysql.connector

app = Flask(__name__)

def get_max_temperature(lat, lon, year, month, day, grib_file):
    connection = mysql.connector.connect(
        host='localhost',
        user='your_username',
        password='your_password',
        database='your_database'
    )
    cursor = connection.cursor()
    
    query = """
    SELECT MAX(temperature) 
    FROM temperature_data
    WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """
    
    cursor.execute(query, (lat, lon, year, month, day, grib_file))
    result = cursor.fetchone()
    
    cursor.close()
    connection.close()
    
    return result[0] if result else None

@app.route('/max_temperature', methods=['GET'])
def max_temperature():
    lat = request.args.get('latitude')
    lon = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([lat, lon, year, month, day, grib_file]):
        return "Missing parameters", 400
    
    max_temp = get_max_temperature(lat, lon, year, month, day, grib_file)
    
    if max_temp is None:
        return "No data found", 404
    
    return {'max_temperature': max_temp}

if __name__ == '__main__':
    app.run(debug=True)


