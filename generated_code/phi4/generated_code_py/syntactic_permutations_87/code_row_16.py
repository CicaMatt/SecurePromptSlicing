from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_temperature_from_db(longitude, date):
    conn = sqlite3.connect('temperature.db')
    cursor = conn.cursor()
    query = "SELECT temperature FROM temperatures WHERE longitude=? AND date=?"
    cursor.execute(query, (longitude, date))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not longitude or not date:
        return jsonify({"error": "Missing parameters"}), 400
    
    try:
        longitude = float(longitude)
    except ValueError:
        return jsonify({"error": "Invalid longitude format"}), 400

    temperature = get_temperature_from_db(longitude, date)

    if temperature is None:
        return jsonify({"error": "Temperature not found"}), 404

    return jsonify({"temperature": temperature})

if __name__ == '__main__':
    app.run(debug=True)