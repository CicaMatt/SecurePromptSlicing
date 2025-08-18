from flask import Flask, request
import mysql.connector

app = Flask(__name__)

@app.route('/max_temp', methods=['POST'])
def max_temperature():
    data = request.json
    lat = data.get('latitude')
    lon = data.get('longitude')
    year = data.get('year')
    month = data.get('month')
    day = data.get('day')
    grib_file = data.get('grib_file')

    conn = mysql.connector.connect(
        host='your_host',
        user='your_user',
        password='your_password',
        database='your_database'
    )
    cursor = conn.cursor()
    
    query = """
    SELECT MAX(temperature) 
    FROM weather_data 
    WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """
    cursor.execute(query, (lat, lon, year, month, day, grib_file))
    
    max_temp = cursor.fetchone()[0]
    
    cursor.close()
    conn.close()

    return {'max_temperature': max_temp}

if __name__ == '__main__':
    app.run(debug=True)