from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect('weather.db')
    cursor = conn.cursor()
    
    query = """
    SELECT temperature 
    FROM temperatures 
    WHERE latitude = ? AND longitude = ? AND date = ?
    LIMIT 1
    """
    
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    conn.close()
    
    if result:
        return result[0]
    else:
        return None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        latitude = float(latitude)
        longitude = float(longitude)
        # Assuming the date is in YYYY-MM-DD format for simplicity
    except ValueError:
        return jsonify({'error': 'Invalid parameter format'}), 400
    
    temperature = get_temperature_from_db(latitude, longitude, date)

    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'message': 'No data found for the given location and date'}), 404

if __name__ == '__main__':
    app.run(debug=True)