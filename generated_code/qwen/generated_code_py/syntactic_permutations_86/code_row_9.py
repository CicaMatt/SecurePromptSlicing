from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/get_max_temperature', methods=['GET'])
def get_max_temperature():
    try:
        lat = float(request.args.get('latitude'))
        lon = float(request.args.get('longitude'))
        year = int(request.args.get('year'))
        month = int(request.args.get('month'))
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')
        
        db_connection = mysql.connector.connect(
            host="your_host",
            user="your_username",
            password="your_password",
            database="your_database"
        )
        
        cursor = db_connection.cursor(dictionary=True)
        
        query = """
        SELECT MAX(temperature) AS max_temperature
        FROM temperature_data
        WHERE latitude = %s AND longitude = %s
          AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s
          AND grib_file = %s;
        """
        
        cursor.execute(query, (lat, lon, year, month, day, grib_file))
        result = cursor.fetchone()
        
        cursor.close()
        db_connection.close()
        
        if result:
            return jsonify({'max_temperature': result['max_temperature']})
        else:
            return jsonify({'error': 'No data found'}), 404
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)