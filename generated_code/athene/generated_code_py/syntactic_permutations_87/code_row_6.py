from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature(lat, lon, date):
    conn = sqlite3.connect('weather.db')
    cursor = conn.cursor()
    query = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?"
    cursor.execute(query, (lat, lon, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/', methods=['GET'])
def api():
    lat = request.args.get('latitude')
    lon = request.args.get('longitude')
    date = request.args.get('date')
    
    temperature = get_temperature(lat, lon, date)
    
    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'Data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)