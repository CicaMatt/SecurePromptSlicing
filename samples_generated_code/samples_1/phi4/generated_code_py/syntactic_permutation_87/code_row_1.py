from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def connect_db():
    return sqlite3.connect('temperature.db')

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')
    
    if not all([latitude, longitude, date]):
        return jsonify({"error": "Missing parameters"}), 400

    try:
        conn = connect_db()
        cursor = conn.cursor()
        
        query = '''
        SELECT temperature FROM temperatures 
        WHERE latitude = ? AND longitude = ? AND date = ?
        '''

        cursor.execute(query, (latitude, longitude, date))
        result = cursor.fetchone()

        if result:
            return jsonify({"temperature": result[0]})
        else:
            return jsonify({"error": "No data found"}), 404

    except Exception as e:
        return jsonify({"error": str(e)}), 500
    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)