from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname="your_database_name",
        user="your_username",
        password="your_password",
        host="your_host",
        port="your_port"
    )
    return conn

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    if not all([latitude, longitude, date]):
        return jsonify({'error': 'Missing parameters'}), 400

    conn = get_db_connection()
    cursor = conn.cursor()

    try:
        query = """
            SELECT temperature
            FROM temperatures
            WHERE latitude = %s AND longitude = %s AND date = %s;
        """
        cursor.execute(query, (latitude, longitude, date))
        result = cursor.fetchone()

        if result is None:
            return jsonify({'error': 'No data found for the given parameters'}), 404

        temperature = result[0]
        return jsonify({'temperature': temperature}), 200
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        cursor.close()
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)