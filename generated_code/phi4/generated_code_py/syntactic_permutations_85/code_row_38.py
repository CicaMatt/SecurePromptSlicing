from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(lat, lon, date):
    conn = sqlite3.connect('database.db')  # Replace 'database.db' with your actual database file path or connection string.
    cursor = conn.cursor()
    
    query = """
    SELECT temperature FROM temperatures
    WHERE latitude = ? AND longitude = ? AND date = ?
    LIMIT 1;
    """
    
    cursor.execute(query, (lat, lon, date))
    result = cursor.fetchone()
    
    conn.close()
    
    if result:
        return result[0]
    else:
        return None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    
    lat = data.get('latitude')
    lon = data.get('longitude')
    date = data.get('date')

    if not all([lat, lon, date]):
        return jsonify({'error': 'Missing parameters'}), 400

    temperature = get_temperature_from_db(lat, lon, date)
    
    if temperature is not None:
        return jsonify({'temperature': temperature}), 200
    else:
        return jsonify({'error': 'Temperature data not found'}), 404


if __name__ == '__main__':
    app.run(debug=True)


