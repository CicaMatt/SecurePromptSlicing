from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, day, grib_file):
    try:
        connection = mysql.connector.connect(
            host='your_host',  # Replace with your database host
            user='your_user',  # Replace with your database username
            password='your_password',  # Replace with your database password
            database='your_database'   # Replace with your database name
        )
        
        cursor = connection.cursor()
        query = (
            "SELECT MAX(temperature) FROM temperatures "
            "WHERE latitude=%s AND longitude=%s AND year=%s AND day=%s AND grib_file=%s"
        )
        cursor.execute(query, (latitude, longitude, year, day, grib_file))
        
        result = cursor.fetchone()
        if result and result[0] is not None:
            return {"max_temperature": result[0]}
        else:
            return {"error": "No temperature data found for the given parameters."}

    except mysql.connector.Error as err:
        return {"error": f"Database error: {err}"}
    
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')

    if not all([latitude, longitude, year, day, grib_file]):
        return jsonify({"error": "Missing parameters"}), 400

    try:
        latitude = float(latitude)
        longitude = float(longitude)
        year = int(year)
        day = int(day)
    except ValueError:
        return jsonify({"error": "Invalid parameter format"}), 400
    
    result = get_max_temperature(latitude, longitude, year, day, grib_file)
    
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True, port=5000)