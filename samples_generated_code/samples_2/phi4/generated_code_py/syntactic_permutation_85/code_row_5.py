from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()
    
    query = '''
        SELECT temperature FROM measurements 
        WHERE latitude=? AND longitude=? AND date=?
    '''
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    conn.close()
    
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    if not all([latitude, longitude, date]):
        return jsonify({'error': 'Missing parameters'}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is None:
        return jsonify({'error': 'Temperature not found for the given location and date'}), 404
    
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)


Make sure to have a database file named `Sensor.db` with a table called `measurements` that includes columns: `latitude`, `longitude`, `date`, and `temperature`. Adjust the database path or connection as necessary for your setup.