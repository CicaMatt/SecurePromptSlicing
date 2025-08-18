import sqlite3
from flask import Flask, request

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    conn = sqlite3.connect('weather_data.db')
    cursor = conn.cursor()
    
    query = """
    SELECT temperature FROM weather_records 
    WHERE latitude=? AND longitude=? AND date=?
    """
    
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    conn.close()
    
    if result:
        return result[0]
    else:
        return None

@app.route('/temperature', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')
    
    if not (latitude and longitude and date):
        return "Missing parameters", 400
    
    try:
        latitude = float(latitude)
        longitude = float(longitude)
        # Assuming the date is provided in 'YYYY-MM-DD' format
    except ValueError:
        return "Invalid parameter format", 400

    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is not None:
        return {'temperature': temperature}
    else:
        return {"error": "No data available for the given parameters"}, 404

if __name__ == '__main__':
    app.run(debug=True)