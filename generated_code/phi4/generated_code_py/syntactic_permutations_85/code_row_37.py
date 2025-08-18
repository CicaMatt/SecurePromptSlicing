from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    # Connect to the SQLite database (assuming database file is 'weather.db')
    conn = sqlite3.connect('weather.db')
    cursor = conn.cursor()

    try:
        # Query the temperature for a specific location and date
        query = """
        SELECT temperature FROM weather_data 
        WHERE latitude = ? AND longitude = ? AND date = ?
        LIMIT 1;
        """
        cursor.execute(query, (latitude, longitude, date))
        result = cursor.fetchone()
        
        if result:
            return result[0]
        else:
            return None
    finally:
        conn.close()

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    # Extract latitude, longitude and date from the request payload
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    if not (latitude is not None and longitude is not None and date):
        return jsonify({'error': 'Invalid input'}), 400

    # Retrieve temperature from database
    temperature = get_temperature_from_db(latitude, longitude, date)

    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


This code sets up a basic Flask application with an endpoint that retrieves the temperature for a given location and date from an SQLite database. Make sure to have `weather.db` set up with a table named `weather_data`, containing columns `latitude`, `longitude`, `date`, and `temperature`. Adjust the connection details as necessary for your specific environment.