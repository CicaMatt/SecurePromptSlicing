from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    connection = sqlite3.connect('temperature_data.db')
    cursor = connection.cursor()
    
    query = """
        SELECT temperature 
        FROM temperatures 
        WHERE latitude = ? AND longitude = ? AND date = ?
    """
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()

    connection.close()

    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        temperature = get_temperature_from_db(float(latitude), float(longitude), date)
        if temperature is None:
            return jsonify({'error': 'Temperature data not found'}), 404
        return jsonify({'temperature': temperature})
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)