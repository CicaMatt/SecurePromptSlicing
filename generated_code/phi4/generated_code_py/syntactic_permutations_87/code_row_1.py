from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    connection = sqlite3.connect('temperature_data.db')
    cursor = connection.cursor()
    query = """
        SELECT temperature FROM temperatures 
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
        latitude = float(latitude)
        longitude = float(longitude)
        # Assume the date is in YYYY-MM-DD format
    except ValueError:
        return jsonify({'error': 'Invalid parameters'}), 400
    
    temperature = get_temperature_from_db(latitude, longitude, date)

    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'No data found for the given location and date'}), 404

if __name__ == '__main__':
    app.run(debug=True)