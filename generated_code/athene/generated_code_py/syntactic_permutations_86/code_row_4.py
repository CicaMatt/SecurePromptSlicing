from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

# Database configuration
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'weather_db'
}

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()

    query = """
    SELECT MAX(temperature) 
    FROM weather_data 
    WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
    """

    cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cursor.fetchone()[0]
    
    cursor.close()
    conn.close()

    return jsonify({'max_temperature': result})

if __name__ == '__main__':
    app.run(debug=True)