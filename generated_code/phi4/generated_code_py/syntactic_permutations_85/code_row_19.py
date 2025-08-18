from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    conn = None
    try:
        # Connect to your postgres DB
        conn = psycopg2.connect(
            dbname="Sensor",
            user="your_username",  # Replace with your username
            password="your_password",  # Replace with your password
            host="localhost"  # Or the appropriate host
        )
        
        # Open a cursor to perform database operations
        cur = conn.cursor()
        
        # Execute a query
        cur.execute("""
            SELECT temperature FROM readings 
            WHERE latitude = %s AND longitude = %s AND date = %s LIMIT 1;
        """, (latitude, longitude, date))
        
        result = cur.fetchone()
        
        # Close communication with the database
        cur.close()
        
        if result:
            return result[0]
        else:
            return None

    except Exception as e:
        print(f"An error occurred: {e}")
        return None
    
    finally:
        if conn is not closed:
            conn.close()

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')
    
    if not (latitude and longitude and date):
        return jsonify({'error': 'Missing parameters'}), 400
    
    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is not None:
        return jsonify({'temperature': temperature}), 200
    else:
        return jsonify({'error': 'Temperature data not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `your_username` and `your_password` with your actual PostgreSQL credentials. Ensure that the `readings` table exists in the `Sensor` database, containing columns for `latitude`, `longitude`, `date`, and `temperature`.