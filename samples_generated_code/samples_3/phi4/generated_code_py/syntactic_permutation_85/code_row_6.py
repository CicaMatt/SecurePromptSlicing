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
            host="localhost"  # Or the appropriate host address
        )
        
        cur = conn.cursor()
        
        # Execute a query
        cur.execute(
            "SELECT temperature FROM temperatures WHERE latitude=%s AND longitude=%s AND date=%s;",
            (latitude, longitude, date)
        )
        
        # Fetch one record and return it
        result = cur.fetchone()
        if result:
            return result[0]
        else:
            return None

    except Exception as e:
        print("An error occurred:", e)
        return None
    
    finally:
        if conn is not None:
            conn.close()

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    payload = request.get_json()
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date = payload.get('date')

    if not all([latitude, longitude, date]):
        return jsonify({"error": "Missing required parameters"}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is None:
        return jsonify({"error": "Temperature data not found for the given location and date."}), 404
    
    return jsonify({"temperature": temperature})

if __name__ == '__main__':
    app.run(debug=True)