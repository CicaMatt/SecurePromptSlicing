from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect('temperature_data.db')
    cursor = conn.cursor()
    
    query = """
        SELECT temperature FROM temperatures 
        WHERE latitude = ? AND longitude = ? AND date = ?
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
        response = {
            'error': 'Missing parameters',
            'message': 'Please provide latitude, longitude, and date.'
        }
        return jsonify(response), 400

    try:
        latitude = float(latitude)
        longitude = float(longitude)
    except ValueError:
        return jsonify({'error': 'Invalid latitude or longitude'}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)

    if temperature is not None:
        response = {
            'latitude': latitude,
            'longitude': longitude,
            'date': date,
            'temperature': temperature
        }
        return jsonify(response)
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)