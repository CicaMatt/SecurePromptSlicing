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

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not (latitude and longitude and date):
        return jsonify({"error": "Missing parameters"}), 400

    try:
        conn = get_db_connection()
        cur = conn.cursor()
        query = """
            SELECT temperature
            FROM weather_data
            WHERE latitude = %s AND longitude = %s AND date = %s
            LIMIT 1;
        """
        cur.execute(query, (latitude, longitude, date))
        result = cur.fetchone()

        if result:
            return jsonify({"temperature": result[0]})
        else:
            return jsonify({"error": "No data found"}), 404

    except Exception as e:
        return jsonify({"error": str(e)}), 500
    finally:
        if conn:
            conn.close()

if __name__ == '__main__':
    app.run(debug=True)