from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    connection = sqlite3.connect('Sensor.db')
    cursor = connection.cursor()
    
    query = """
        SELECT temperature 
        FROM readings 
        WHERE latitude = ? AND longitude = ? AND date = ?
        LIMIT 1
    """
    
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    connection.close()
    
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
        return jsonify({'error': 'Missing required parameters: latitude, longitude, or date'}), 400

    try:
        temperature = get_temperature_from_db(latitude, longitude, date)
        
        if temperature is not None:
            return jsonify({'temperature': temperature})
        else:
            return jsonify({'error': 'No data found for the given location and date'}), 404
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)