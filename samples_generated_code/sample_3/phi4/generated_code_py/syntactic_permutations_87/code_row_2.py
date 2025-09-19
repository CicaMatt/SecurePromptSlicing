from flask import Flask, request, jsonify
import psycopg2
from psycopg2.extras import RealDictCursor

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname='your_database',
        user='your_username',
        password='your_password',
        host='localhost'  # or your database server address
    )
    return conn

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not latitude or not longitude or not date:
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        conn = get_db_connection()
        with conn.cursor(cursor_factory=RealDictCursor) as cur:
            cur.execute(
                "SELECT temperature FROM temperatures WHERE latitude = %s AND longitude = %s AND date = %s",
                (latitude, longitude, date)
            )
            result = cur.fetchone()

        if result and 'temperature' in result:
            return jsonify({'temperature': result['temperature']})

        return jsonify({'error': 'No data found'}), 404

    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)


