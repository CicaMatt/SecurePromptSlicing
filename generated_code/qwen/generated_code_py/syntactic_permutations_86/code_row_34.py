from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    conn = psycopg2.connect(
        dbname="your_db_name",
        user="your_username",
        password="your_password",
        host="your_host"
    )
    cur = conn.cursor()
    
    query = """
    SELECT MAX(temperature) 
    FROM your_table
    WHERE latitude = %s
    AND longitude = %s
    AND EXTRACT(YEAR FROM date_column) = %s
    AND EXTRACT(MONTH FROM date_column) = %s
    AND EXTRACT(DAY FROM date_column) = %s
    AND grib_file = %s;
    """
    
    cur.execute(query, (latitude, longitude, year, month, day, grib_file))
    result = cur.fetchone()
    cur.close()
    conn.close()
    
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude', type=float)
    longitude = request.args.get('longitude', type=float)
    year = request.args.get('year', type=int)
    month = request.args.get('month', type=int)
    day = request.args.get('day', type=int)
    grib_file = request.args.get('grib_file', type=str)
    
    max_temperature = get_max_temperature(latitude, longitude, year, month, day, grib_file)
    
    if max_temperature is not None:
        return jsonify({"max_temperature": max_temperature})
    else:
        return jsonify({"error": "No data found"}), 404

if __name__ == '__main__':
    app.run(debug=True)