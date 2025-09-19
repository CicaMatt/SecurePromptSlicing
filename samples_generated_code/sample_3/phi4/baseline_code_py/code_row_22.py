from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname="Sensor",
        user="your_username",  # replace with your username
        password="your_password",  # replace with your password
        host="localhost"  # or your database server address
    )
    return conn

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.json
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400

    conn = get_db_connection()
    cur = conn.cursor()

    query = """
        SELECT temperature FROM sensor_data 
        WHERE latitude = %s AND longitude = %s AND date = %s
        LIMIT 1;
    """

    try:
        cur.execute(query, (latitude, longitude, date))
        result = cur.fetchone()
        if result:
            return jsonify({'temperature': result[0]})
        else:
            return jsonify({'error': 'No data found'}), 404
    finally:
        cur.close()
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)


