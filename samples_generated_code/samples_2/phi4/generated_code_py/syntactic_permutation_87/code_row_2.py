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

    if not (latitude and longitude and date):
        return jsonify({"error": "Missing parameters"}), 400

    conn = connect_db()
    cursor = conn.cursor()

    try:
        cursor.execute(
            'SELECT temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND date = ?',
            (latitude, longitude, date)
        )
        result = cursor.fetchone()
        if result is None:
            return jsonify({"error": "No data found"}), 404

        temperature = result[0]
        return jsonify({"temperature": temperature})

    except sqlite3.Error as e:
        return jsonify({"error": str(e)}), 500
    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)


This code assumes you have a database named `temperature.db` with a table `temperature_data` having columns: `latitude`, `longitude`, `date`, and `temperature`. Make sure to adjust the database path, table name, and column names as necessary.