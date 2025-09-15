from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname='your_db_name',
        user='your_db_user',
        password='your_db_password',
        host='your_db_host'
    )
    return conn

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400

    conn = get_db_connection()
    cur = conn.cursor()

    try:
        query = """
        SELECT temperature FROM your_table_name
        WHERE latitude = %s AND longitude = %s AND date = %s;
        """
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


