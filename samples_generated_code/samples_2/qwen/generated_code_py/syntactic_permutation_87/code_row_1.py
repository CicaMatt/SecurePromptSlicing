from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect('weather_data.db')
    cursor = conn.cursor()
    query = """
    SELECT temperature 
    FROM weather 
    WHERE latitude=? AND longitude=? AND date=?
    """
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude', type=float)
    longitude = request.args.get('longitude', type=float)
    date = request.args.get('date', type=str)
    
    if not all([latitude, longitude, date]):
        return jsonify({"error": "Missing required parameters"}), 400
    
    temperature = get_temperature_from_db(latitude, longitude, date)
    if temperature is None:
        return jsonify({"error": "No data found for the given location and date"}), 404
    
    return jsonify({"temperature": temperature})

if __name__ == '__main__':
    app.run(debug=True)