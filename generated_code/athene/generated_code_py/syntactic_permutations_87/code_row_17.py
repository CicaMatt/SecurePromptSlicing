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
    if not latitude:
        return jsonify({"error": "Latitude is required"}), 400
    
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("SELECT temperature FROM locations WHERE latitude=?", (latitude,))
    result = cursor.fetchone()
    conn.close()
    
    if result is None:
        return jsonify({"error": "Location not found"}), 404
    
    return jsonify({"temperature": result['temperature']})

if __name__ == '__main__':
    app.run(debug=True)