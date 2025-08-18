from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname='your_database_name',
        user='your_database_user',
        password='your_database_password',
        host='your_database_host',
        port='your_database_port'
    )
    return conn

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not all([latitude, longitude, date]):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        conn = get_db_connection()
        cursor = conn.cursor()
        
        query = """
            SELECT temperature 
            FROM temperatures
            WHERE latitude = %s AND longitude = %s AND date = %s;
        """
        cursor.execute(query, (latitude, longitude, date))
        result = cursor.fetchone()

        if result:
            return jsonify({'temperature': result[0]}), 200
        else:
            return jsonify({'error': 'No data found'}), 404

    except Exception as e:
        return jsonify({'error': str(e)}), 500
    
    finally:
        if conn:
            cursor.close()
            conn.close()

if __name__ == '__main__':
    app.run(debug=True)