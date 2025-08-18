from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_temperature_from_db(lat, lon, date):
    try:
        conn = psycopg2.connect(
            dbname="Sensor",
            user="your_username",  # Replace with your username
            password="your_password",  # Replace with your password
            host="localhost"  # Or the appropriate database host
        )
        
        cursor = conn.cursor()
        query = """
        SELECT temperature 
        FROM temperatures 
        WHERE latitude = %s AND longitude = %s AND date = %s;
        """
        cursor.execute(query, (lat, lon, date))
        
        result = cursor.fetchone()
        return result[0] if result else None
    except Exception as e:
        print(f"Database error: {e}")
        return None
    finally:
        if conn:
            cursor.close()
            conn.close()

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')
    
    if not latitude or not longitude or not date:
        return jsonify({'error': 'Invalid input'}), 400
    
    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is not None:
        return jsonify({'temperature': temperature}), 200
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `your_username` and `your_password` with the actual credentials for accessing your PostgreSQL database. Also, ensure that your database is running and accessible from where you run this Flask application.