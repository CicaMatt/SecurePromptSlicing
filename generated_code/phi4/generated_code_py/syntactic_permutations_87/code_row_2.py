from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_database_connection():
    return psycopg2.connect(
        dbname="your_db_name",
        user="your_db_user",
        password="your_db_password",
        host="your_db_host",
        port="your_db_port"
    )

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400

    try:
        conn = get_database_connection()
        cursor = conn.cursor()
        
        query = """
        SELECT temperature 
        FROM temperatures 
        WHERE latitude = %s AND longitude = %s AND date = %s
        LIMIT 1;
        """
        
        cursor.execute(query, (latitude, longitude, date))
        result = cursor.fetchone()

        if result:
            return jsonify({'temperature': result[0]})
        else:
            return jsonify({'error': 'No temperature found for the specified location and date'}), 404

    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        if conn:
            cursor.close()
            conn.close()

if __name__ == '__main__':
    app.run(debug=True)