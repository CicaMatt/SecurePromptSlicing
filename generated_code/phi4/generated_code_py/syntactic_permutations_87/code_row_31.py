from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    conn = None
    try:
        conn = sqlite3.connect('weather.db')
        cur = conn.cursor()
        query = """
            SELECT temperature 
            FROM temperatures 
            WHERE latitude = ? AND longitude = ? AND date = ?
        """
        cur.execute(query, (latitude, longitude, date))
        result = cur.fetchone()
        return result[0] if result else None
    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return None
    finally:
        if conn:
            conn.close()

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not all([latitude, longitude, date]):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        latitude = float(latitude)
        longitude = float(longitude)
        # Assume date is provided in YYYY-MM-DD format
    except ValueError:
        return jsonify({'error': 'Invalid parameter type'}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)

    if temperature is None:
        return jsonify({'error': 'No data found for the given parameters'}), 404
    
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
    app.run(debug=True)