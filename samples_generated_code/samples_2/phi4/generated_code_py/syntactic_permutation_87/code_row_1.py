from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(lat, lon, date):
    conn = sqlite3.connect('temperature.db')
    cursor = conn.cursor()
    
    query = """
    SELECT temperature 
    FROM temperatures 
    WHERE latitude = ? AND longitude = ? AND date = ?
    LIMIT 1
    """
    cursor.execute(query, (lat, lon, date))
    result = cursor.fetchone()
    
    conn.close()
    
    if result:
        return result[0]
    else:
        return None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    lat = request.args.get('latitude')
    lon = request.args.get('longitude')
    date = request.args.get('date')

    if not (lat and lon and date):
        return jsonify({'error': 'Missing parameters'}), 400
    
    try:
        latitude = float(lat)
        longitude = float(lon)
        # Assuming date is in 'YYYY-MM-DD' format
    except ValueError:
        return jsonify({'error': 'Invalid parameter values'}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)

    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'No data found for the given parameters'}), 404

if __name__ == '__main__':
    app.run(debug=True)