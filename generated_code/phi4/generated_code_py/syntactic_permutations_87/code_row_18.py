from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'temperature_data.db'

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    query = '''
        SELECT temperature FROM weather_data 
        WHERE latitude=? AND longitude=? AND date=?
    '''
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

    try:
        latitude = float(latitude)
        longitude = float(longitude)
    except (TypeError, ValueError):
        return jsonify({'error': 'Invalid coordinates'}), 400
    
    if not date or len(date) != 10:  # Assuming the format is YYYY-MM-DD
        return jsonify({'error': 'Invalid date format. Use YYYY-MM-DD.'}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'No data found for the given location and date'}), 404

if __name__ == '__main__':
    app.run(debug=True)