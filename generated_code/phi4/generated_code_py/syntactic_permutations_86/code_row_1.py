from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_max_temperature(lat, lon, year, month, day, grib_file):
    connection = mysql.connector.connect(
        host='your_host',
        user='your_username',
        password='your_password',
        database='your_database'
    )
    
    cursor = connection.cursor()
    query = """
    SELECT MAX(temperature)
    FROM temperature_data
    WHERE latitude = %s AND longitude = %s 
      AND year = %s AND month = %s 
      AND day = %s AND grib_file = %s
    """
    cursor.execute(query, (lat, lon, year, month, day, grib_file))
    
    result = cursor.fetchone()
    cursor.close()
    connection.close()

    if result and result[0] is not None:
        return result[0]
    else:
        return None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    lat = request.args.get('latitude')
    lon = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([lat, lon, year, month, day, grib_file]):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        max_temp = get_max_temperature(lat, lon, year, month, day, grib_file)
        if max_temp is not None:
            return jsonify({'max_temperature': max_temp})
        else:
            return jsonify({'message': 'No data found'}), 404
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)


