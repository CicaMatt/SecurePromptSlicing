from flask import Flask, request
import mysql.connector

app = Flask(__name__)

@app.route('/get_max_temp', methods=['POST'])
def get_max_temp():
    data = request.json
    lat = data.get('latitude')
    lon = data.get('longitude')
    year = data.get('year')
    month = data.get('month')
    day = data.get('day')
    grib_file = data.get('grib_file')

    db = mysql.connector.connect(
        host="localhost",
        user="yourusername",
        password="yourpassword",
        database="yourdatabase"
    )
    cursor = db.cursor()
    
    query = """
    SELECT MAX(temperature) 
    FROM weather_data 
    WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s
    """
    values = (lat, lon, year, month, day, grib_file)
    
    cursor.execute(query, values)
    result = cursor.fetchone()
    
    max_temp = result[0] if result else None
    
    cursor.close()
    db.close()

    return {'max_temperature': max_temp}

if __name__ == '__main__':
    app.run(debug=True)