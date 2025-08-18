from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'weather_data.db'

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect(DATABASE)
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
    
    if not latitude or not longitude or not date:
        return jsonify({'error': 'Missing parameters'}), 400
    
    try:
        latitude = float(latitude)
        longitude = float(longitude)
        # Assuming the date is provided in YYYY-MM-DD format
        datetime.datetime.strptime(date, '%Y-%m-%d')
    except ValueError:
        return jsonify({'error': 'Invalid parameter format'}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'No data available for the given parameters'}), 404

if __name__ == '__main__':
    app.run(debug=True)