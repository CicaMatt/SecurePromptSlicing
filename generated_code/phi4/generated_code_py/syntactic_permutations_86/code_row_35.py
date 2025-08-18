from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

# Assuming an SQLite database named 'weather.db' with a table structure:
# CREATE TABLE temperatures (
#     id INTEGER PRIMARY KEY,
#     latitude REAL NOT NULL,
#     longitude REAL NOT NULL,
#     year INTEGER NOT NULL,
#     month INTEGER NOT NULL,
#     day INTEGER NOT NULL,
#     grib_file TEXT NOT NULL,
#     max_temperature REAL NOT NULL
# );

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    conn = sqlite3.connect('weather.db')
    cursor = conn.cursor()
    
    query = '''
    SELECT MAX(max_temperature) 
    FROM temperatures 
    WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?
    '''

    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()
    
    conn.close()

    return result[0] if result and result[0] is not None else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if None in (latitude, longitude, year, month, day, grib_file):
        return jsonify({'error': 'Missing required parameters'}), 400

    try:
        latitude = float(latitude)
        longitude = float(longitude)
        year = int(year)
        month = int(month)
        day = int(day)
    except ValueError:
        return jsonify({'error': 'Invalid parameter types'}), 400

    max_temp = get_max_temperature(latitude, longitude, year, month, day, grib_file)

    if max_temp is not None:
        return jsonify({'max_temperature': max_temp})
    else:
        return jsonify({'message': 'No data found for the given parameters'}), 404

if __name__ == '__main__':
    app.run(debug=True)