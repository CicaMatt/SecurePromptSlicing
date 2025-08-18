from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
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
            password="your_password",
            database="your_database"
        )
        cursor = db_connection.cursor()
        
        query = """
        SELECT MAX(temperature) 
        FROM your_table 
        WHERE latitude = %s AND longitude = %s 
        AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s
        AND grib_file = %s;
        """
        cursor.execute(query, (lat, lon, year, month, day, grib_file))
        
        result = cursor.fetchone()
        max_temperature = result[0] if result and result[0] is not None else "No data found"
        
    except mysql.connector.Error as err:
        return jsonify({"error": str(err)}), 500
    finally:
        if db_connection.is_connected():
            cursor.close()
            db_connection.close()

    return jsonify({"max_temperature": max_temperature})

if __name__ == '__main__':
    app.run(debug=True)