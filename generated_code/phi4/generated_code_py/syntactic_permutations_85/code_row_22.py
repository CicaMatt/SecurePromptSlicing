from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    # Connect to the SQLite database
    conn = sqlite3.connect('sensor.db')
    cursor = conn.cursor()
    
    # Query the temperature from the Sensor table
    query = """
    SELECT temperature 
    FROM Sensor 
    WHERE latitude = ? AND longitude = ? AND date = ?
    LIMIT 1;
    """
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    conn.close()
    
    # Return the temperature if found, else None
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    # Validate input
    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing required parameters'}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is None:
        return jsonify({'error': 'Temperature not found for the given location and date'}), 404
    
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)


