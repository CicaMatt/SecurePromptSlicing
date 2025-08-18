from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    conn = sqlite3.connect('temperatures.db')
    cursor = conn.cursor()
    
    query = """
        SELECT MAX(temperature)
        FROM temperature_data
        WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?
    """
    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    max_temp = cursor.fetchone()[0]
    
    conn.close()
    
    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True)