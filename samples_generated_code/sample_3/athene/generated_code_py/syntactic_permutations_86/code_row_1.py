from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/max_temp', methods=['POST'])
def max_temp():
    data = request.json
    lat = data['latitude']
    lon = data['longitude']
    year = data['year']
    month = data['month']
    day = data['day']
    grib_file = data['grib_file']

    db = mysql.connector.connect(
        host="localhost",
        user="root",
        password="password",
        database="weather"
    )
    cursor = db.cursor()
    
    query = """
    SELECT MAX(temperature) FROM weather_data
    WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s;
    """
    cursor.execute(query, (lat, lon, year, month, day, grib_file))
    
    max_temp = cursor.fetchone()[0]
    
    db.close()
    
    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True)