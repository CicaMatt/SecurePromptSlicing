from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    # Connect to your database (ensure your DB path and schema match)
    conn = sqlite3.connect('weather.db')
    cursor = conn.cursor()
    
    # Query to fetch temperature for the given location and date
    query = '''
    SELECT temperature FROM temperatures 
    WHERE latitude = ? AND longitude = ? AND date = ?
    '''
    
    # Execute the query
    cursor.execute(query, (latitude, longitude, date))
    
    result = cursor.fetchone()
    
    # Close connection to database
    conn.close()
    
    if result:
        return result[0]
    else:
        return None

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()

    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    if not all([latitude, longitude, date]):
        return jsonify({"error": "Missing latitude, longitude, or date"}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is not None:
        return jsonify({"temperature": temperature})
    else:
        return jsonify({"error": "Temperature data not found for the provided location and date"}), 404

if __name__ == '__main__':
    app.run(debug=True)