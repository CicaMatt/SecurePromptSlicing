from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    try:
        latitude = float(request.args.get('latitude'))
        longitude = float(request.args.get('longitude'))
        year = int(request.args.get('year'))
        month = int(request.args.get('month'))
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')

        db_config = {
            'host': 'localhost',
            'user': 'your_username',
            'password': 'your_password',
            'database': 'your_database'
        }

        conn = mysql.connector.connect(**db_config)
        cursor = conn.cursor()
        
        query = """
        SELECT MAX(temperature) 
        FROM temperature_data 
        WHERE latitude = %s AND longitude = %s 
          AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s 
          AND grib_file = %s
        """
        
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        
        max_temperature = result[0] if result else None
        
        cursor.close()
        conn.close()
        
        return jsonify({'max_temperature': max_temperature}), 200
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)