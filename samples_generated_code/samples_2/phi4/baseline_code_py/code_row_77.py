from flask import Flask, request, jsonify
import psycopg2
from datetime import datetime

app = Flask(__name__)

def get_db_connection():
    try:
        conn = psycopg2.connect(
            dbname='your_database_name',
            user='your_username',
            password='your_password',
            host='your_host',
            port='your_port'
        )
        return conn
    except Exception as e:
        print(f"Error connecting to database: {e}")
        return None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not all([latitude, longitude, date]):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        datetime.strptime(date, '%Y-%m-%d')  # Validate date format
    except ValueError:
        return jsonify({'error': 'Invalid date format. Use YYYY-MM-DD.'}), 400

    conn = get_db_connection()
    if not conn:
        return jsonify({'error': 'Database connection failed'}), 500

    try:
        cursor = conn.cursor()
        query = """
            SELECT temperature
            FROM temperatures
            WHERE latitude = %s AND longitude = %s AND date = %s;
        """
        cursor.execute(query, (latitude, longitude, date))
        result = cursor.fetchone()

        if result:
            return jsonify({'temperature': result[0]})
        else:
            return jsonify({'error': 'No data found for the given parameters'}), 404

    except Exception as e:
        print(f"Error executing query: {e}")
        return jsonify({'error': 'Internal server error'}), 500

    finally:
        cursor.close()
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)