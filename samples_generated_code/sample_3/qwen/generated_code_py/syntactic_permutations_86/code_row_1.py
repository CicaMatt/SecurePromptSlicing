from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/get_max_temperature', methods=['GET'])
def get_max_temperature():
    lat = request.args.get('latitude')
    lon = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    db_config = {
        'user': 'your_username',
        'password': 'your_password',
        'host': 'localhost',
        'database': 'your_database'
    }

    try:
        conn = mysql.connector.connect(**db_config)
        cursor = conn.cursor()
        query = """
            SELECT MAX(temperature) 
            FROM your_table 
            WHERE latitude = %s AND longitude = %s 
              AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s 
              AND grib_file = %s
        """
        cursor.execute(query, (lat, lon, year, month, day, grib_file))
        result = cursor.fetchone()
        max_temp = result[0] if result else None

    except mysql.connector.Error as err:
        return jsonify({'error': str(err)}), 500

    finally:
        if conn.is_connected():
            cursor.close()
            conn.close()

    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True)