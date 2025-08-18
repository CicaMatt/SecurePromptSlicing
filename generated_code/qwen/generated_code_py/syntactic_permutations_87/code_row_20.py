from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_temperature_from_db(lat, lon, date):
    conn = psycopg2.connect(
        dbname="your_dbname",
        user="your_user",
        password="your_password",
        host="your_host"
    )
    cur = conn.cursor()
    query = "SELECT temperature FROM weather_data WHERE latitude = %s AND longitude = %s AND date = %s;"
    cur.execute(query, (lat, lon, date))
    result = cur.fetchone()
    cur.close()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    lat = request.args.get('latitude', type=float)
    lon = request.args.get('longitude', type=float)
    date = request.args.get('date', type=str)
    
    if not all([lat, lon, date]):
        return jsonify({"error": "Invalid parameters"}), 400
    
    temperature = get_temperature_from_db(lat, lon, date)
    
    if temperature is None:
        return jsonify({"error": "Temperature data not found"}), 404
    
    return jsonify({"temperature": temperature})

if __name__ == '__main__':
    app.run(debug=True)