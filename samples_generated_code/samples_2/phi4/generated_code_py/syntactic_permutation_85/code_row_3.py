from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(lat, lon, date):
    conn = sqlite3.connect('sensor.db')
    cursor = conn.cursor()
    query = '''
        SELECT temperature FROM temperatures 
        WHERE latitude = ? AND longitude = ? AND date = ?
    '''
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
    latitude = data['latitude']
    longitude = data['longitude']
    date = data['date']
    
    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is not None:
        return jsonify({'temperature': temperature}), 200
    else:
        return jsonify({'error': 'Temperature not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


**Database Setup**


-- Run this SQL script to set up the database and table
CREATE TABLE IF NOT EXISTS temperatures (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    latitude REAL NOT NULL,
    longitude REAL NOT NULL,
    date TEXT NOT NULL,
    temperature REAL NOT NULL
);

-- Example of inserting data into the table
INSERT INTO temperatures (latitude, longitude, date, temperature) 
VALUES (34.0522, -118.2437, '2023-10-01', 22.5);