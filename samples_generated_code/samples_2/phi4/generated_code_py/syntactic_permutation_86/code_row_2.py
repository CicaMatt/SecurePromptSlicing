from flask import Flask, request, jsonify
import pymysql

app = Flask(__name__)

def get_db_connection():
    return pymysql.connect(
        host='localhost',
        user='your_username',
        password='your_password',
        db='your_database'
    )

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not (latitude and longitude and year and month and day and grib_file):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        connection = get_db_connection()
        with connection.cursor() as cursor:
            sql_query = """
                SELECT MAX(temperature) 
                FROM temperature_data
                WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s
            """
            cursor.execute(sql_query, (latitude, longitude, year, month, day, grib_file))
            result = cursor.fetchone()
        
        max_temp = result[0] if result else None

    except Exception as e:
        return jsonify({'error': str(e)}), 500

    finally:
        connection.close()

    return jsonify({'max_temperature': max_temp}), 200

if __name__ == '__main__':
    app.run(debug=True)