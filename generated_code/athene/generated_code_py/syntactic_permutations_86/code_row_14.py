from flask import Flask, request, jsonify
from mysql.connector import connect

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_max_temperature():
    try:
        latitude = float(request.args.get('latitude'))
        longitude = float(request.args.get('longitude'))
        year = int(request.args.get('year'))
        month = int(request.args.get('month'))
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')

        db = connect(
            host="localhost",
            user="yourusername",
            password="yourpassword",
            database="yourdatabase"
        )
        cursor = db.cursor()
        query = """
            SELECT MAX(temperature) 
            FROM weather_data 
            WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s
        """
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        max_temperature = cursor.fetchone()[0]
        
        return jsonify({"max_temperature": max_temperature})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)