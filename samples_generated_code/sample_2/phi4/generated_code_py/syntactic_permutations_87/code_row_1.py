from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def connect_db():
    return sqlite3.connect('temperature_data.db')

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')
    
    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400
    
    conn = connect_db()
    cursor = conn.cursor()
    
    query = """
    SELECT temperature FROM weather_data 
    WHERE latitude = ? AND longitude = ? AND date = ?
    LIMIT 1
    """
    
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    
    if result:
        return jsonify({'temperature': result[0]})
    else:
        return jsonify({'error': 'Data not found'}), 404
    
    conn.close()

if __name__ == '__main__':
    app.run(debug=True)