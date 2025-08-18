from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(lat, lon, date):
    connection = sqlite3.connect('Sensor.db')
    cursor = connection.cursor()
    
    query = """
    SELECT temperature 
    FROM readings 
    WHERE latitude=? AND longitude=? AND date=?
    LIMIT 1
    """
    cursor.execute(query, (lat, lon, date))
    result = cursor.fetchone()
    
    connection.close()
    
    return result[0] if result else None

@app.route('/api/', methods=['POST'])
def api_endpoint():
    data = request.get_json()
    lat = data.get('latitude')
    lon = data.get('longitude')
    date = data.get('date')

    if not all([lat, lon, date]):
        return jsonify({'error': 'Missing required parameters'}), 400

    temperature = get_temperature_from_db(lat, lon, date)
    
    if temperature is None:
        return jsonify({'error': 'No temperature found for the given coordinates and date'}), 404
    
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)