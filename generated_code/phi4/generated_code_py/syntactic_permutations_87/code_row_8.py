from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect('temperature.db')
    cursor = conn.cursor()
    query = '''
        SELECT temperature 
        FROM temperatures 
        WHERE latitude = ? AND longitude = ? AND date = ?
    '''
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not (latitude and longitude and date):
        return jsonify({"error": "Missing parameters"}), 400

    try:
        float(latitude)
        float(longitude)
    except ValueError:
        return jsonify({"error": "Invalid latitude or longitude"}), 400
    
    temperature = get_temperature_from_db(float(latitude), float(longitude), date)

    if temperature is None:
        return jsonify({"error": "No data found for the provided parameters"}), 404

    return jsonify({"temperature": temperature}), 200

if __name__ == '__main__':
    app.run(debug=True)