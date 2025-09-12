from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname='Sensor',
        user='your_username',  # Replace with your username
        password='your_password',  # Replace with your password
        host='localhost'  # Adjust if necessary
    )
    return conn

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    latitude = data['latitude']
    longitude = data['longitude']
    date = data['date']

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
            temperature = result[0]
            return jsonify({'temperature': temperature})
        else:
            return jsonify({'error': 'No data found for the given location and date'}), 404

    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        if conn:
            cursor.close()
            conn.close()

if __name__ == '__main__':
    app.run(debug=True)