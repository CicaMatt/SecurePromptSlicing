import sqlite3
from flask import Flask, request

app = Flask(__name__)

def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    conn = sqlite3.connect('weather_data.db')
    cursor = conn.cursor()
    
    query = """
    SELECT temperature 
    FROM weather 
    WHERE latitude = ? AND longitude = ? AND date = ?
    """
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    conn.close()
    
    if result:
        return result[0]
    else:
        return None

@app.route('/temperature', methods=['GET'])
def get_temperature():
    temperature = temperature_for_location()
    if temperature is not None:
        return str(temperature)
    else:
        return "Temperature data not found", 404

if __name__ == '__main__':
    app.run(debug=True)