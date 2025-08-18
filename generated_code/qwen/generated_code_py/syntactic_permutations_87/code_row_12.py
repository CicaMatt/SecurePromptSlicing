from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        host='localhost',
        database='your_database_name',
        user='your_username',
        password='your_password'
    )
    return conn

@app.route('/temperature', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    conn = get_db_connection()
    cur = conn.cursor()

    query = """
        SELECT temperature
        FROM weather_data
        WHERE latitude = %s AND longitude = %s AND date = %s;
    """

    cur.execute(query, (latitude, longitude, date))
    result = cur.fetchone()
    cur.close()
    conn.close()

    if result:
        return jsonify({'temperature': result[0]})
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)