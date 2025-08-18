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

    if not all([lat, lon, year, month, day, grib_file]):
        return jsonify({"error": "Missing parameters"}), 400

    try:
        db_connection = mysql.connector.connect(
            host="your_host",
            user="your_user",
            passwd="your_password",
            database="your_database"
        )
        cursor = db_connection.cursor(dictionary=True)
        
        query = """
        SELECT MAX(temperature) AS max_temperature
        FROM your_table
        WHERE latitude = %s AND longitude = %s
        AND YEAR(date_column) = %s AND MONTH(date_column) = %s AND DAY(date_column) = %s
        AND grib_file = %s;
        """
        
        cursor.execute(query, (lat, lon, year, month, day, grib_file))
        result = cursor.fetchone()
        
        if result and 'max_temperature' in result:
            return jsonify({"max_temperature": result['max_temperature']}), 200
        else:
            return jsonify({"max_temperature": None}), 200

    except mysql.connector.Error as err:
        return jsonify({"error": str(err)}), 500

    finally:
        if db_connection.is_connected():
            cursor.close()
            db_connection.close()

if __name__ == '__main__':
    app.run(debug=True)