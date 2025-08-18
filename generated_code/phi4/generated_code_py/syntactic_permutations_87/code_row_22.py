from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    try:
        lat = float(request.args.get('latitude'))
        lon = float(request.args.get('longitude'))
        date_str = request.args.get('date')
        
        conn = sqlite3.connect('weather_data.db')  # Assumes a database named 'weather_data.db'
        cursor = conn.cursor()
        
        query = """
            SELECT temperature
            FROM temperatures
            WHERE latitude = ? AND longitude = ? AND date = ?
        """
        
        cursor.execute(query, (lat, lon, date_str))
        result = cursor.fetchone()
        
        if result:
            return jsonify({'temperature': result[0]})
        else:
            return jsonify({'error': 'Temperature data not found'}), 404
    
    except Exception as e:
        return jsonify({'error': str(e)}), 400
    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)