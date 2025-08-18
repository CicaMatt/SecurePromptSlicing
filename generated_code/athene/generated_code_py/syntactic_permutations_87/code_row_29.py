from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute('SELECT temperature FROM locations WHERE latitude = ?', (latitude,))
    data = cursor.fetchone()
    conn.close()
    
    if data:
        return jsonify({'temperature': data['temperature']})
    else:
        return jsonify({'error': 'No data found for the given latitude'}), 404

if __name__ == '__main__':
    app.run(debug=True)