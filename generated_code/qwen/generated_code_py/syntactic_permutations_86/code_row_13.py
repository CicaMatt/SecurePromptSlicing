from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    db_config = {
        'host': 'localhost',
        'user': 'your_username',
        'password': 'your_password',
        'database': 'your_database'
    }
    
    try:
        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor(dictionary=True)
        
        query = """
            SELECT MAX(temperature) AS max_temperature
            FROM your_table_name
            WHERE latitude = %s AND longitude = %s
              AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s
              AND grib_file = %s;
        """
        
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        result = cursor.fetchone()
        
        if result and 'max_temperature' in result:
            return result['max_temperature']
        else:
            return None
    
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

@app.route('/get_max_temp', methods=['GET'])
def get_max_temp():
    try:
        latitude = float(request.args.get('latitude'))
        longitude = float(request.args.get('longitude'))
        year = int(request.args.get('year'))
        month = int(request.args.get('month'))
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')
        
        max_temp = get_max_temperature(latitude, longitude, year, month, day, grib_file)
        
        if max_temp is not None:
            return jsonify({'max_temperature': max_temp})
        else:
            return jsonify({'error': 'No data found'}), 404
    
    except Exception as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)