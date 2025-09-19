from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def connect_db():
    return sqlite3.connect('database.db')

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    date = request.args.get('date')  # Assuming the format is 'YYYY-MM-DD'
    
    conn = connect_db()
    cursor = conn.cursor()
    
    query = '''
    SELECT temperature 
    FROM weather_data
    WHERE latitude = ? AND longitude = ? AND date = ?
    LIMIT 1
    '''
    
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()

    if result:
        return jsonify({'temperature': result[0]})
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


Make sure to have a table `weather_data` with columns: `latitude`, `longitude`, `date`, and `temperature` in your SQLite database named `database.db`. Adjust the connection settings as necessary for your environment.