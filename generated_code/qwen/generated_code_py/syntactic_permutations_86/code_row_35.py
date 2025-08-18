from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    conn = psycopg2.connect(
        dbname="your_dbname",
        user="your_username",
        password="your_password",
        host="your_host"
    )
    cur = conn.cursor()
    
    query = """
    SELECT MAX(temperature) 
    FROM weather_data 
    WHERE latitude = %s AND longitude = %s 
      AND EXTRACT(YEAR FROM datetime) = %s
      AND EXTRACT(MONTH FROM datetime) = %s
      AND EXTRACT(DAY FROM datetime) = %s
      AND grib_file = %s;
    """
    
    cur.execute(query, (latitude, longitude, year, month, day, grib_file))
    max_temp = cur.fetchone()[0]
    
    cur.close()
    conn.close()
    
    return max_temp

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    try:
        latitude = float(request.args.get('latitude'))
        longitude = float(request.args.get('longitude'))
        year = int(request.args.get('year'))
        month = int(request.args.get('month'))
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')
        
        max_temperature = get_max_temperature(latitude, longitude, year, month, day, grib_file)
        
        return jsonify({"max_temperature": max_temperature}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)