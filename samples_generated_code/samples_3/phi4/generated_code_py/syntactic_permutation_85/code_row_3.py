from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    connection = sqlite3.connect('temperature.db')
    cursor = connection.cursor()
    
    query = """
    SELECT temperature 
    FROM weather_data 
    WHERE latitude = ? AND longitude = ? AND date = ?
    LIMIT 1
    """
    
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    connection.close()
    
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.json
    
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')
    
    if not all([latitude, longitude, date]):
        return jsonify({'error': 'Missing required parameters'}), 400

    try:
        temperature = get_temperature_from_db(latitude, longitude, date)
        
        if temperature is None:
            return jsonify({'error': 'No temperature data found for the given location and date'}), 404
        
        return jsonify({'temperature': temperature})
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)