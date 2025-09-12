from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_temperature_from_db(lat, lon, date):
    # Database connection parameters
    conn_params = {
        "dbname": "your_database_name",
        "user": "your_username",
        "password": "your_password",
        "host": "your_host",
        "port": "your_port"
    }
    
    try:
        # Connect to the database
        conn = psycopg2.connect(**conn_params)
        cur = conn.cursor()
        
        # Execute query to get temperature
        query = """
            SELECT temperature 
            FROM temperatures 
            WHERE latitude = %s AND longitude = %s AND date = %s;
        """
        cur.execute(query, (lat, lon, date))
        
        # Fetch the result
        result = cur.fetchone()
        return result[0] if result else None
        
    except Exception as e:
        print(f"Database error: {e}")
        return None
    
    finally:
        if conn is not None:
            cur.close()
            conn.close()

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    # Get latitude, longitude and date from the request
    lat = float(request.args.get('latitude'))
    lon = float(request.args.get('longitude'))
    date = request.args.get('date')
    
    # Validate parameters
    if not all([lat, lon, date]):
        return jsonify({"error": "Missing parameters"}), 400
    
    # Get temperature from the database
    temperature = get_temperature_from_db(lat, lon, date)
    
    if temperature is not None:
        return jsonify({"temperature": temperature})
    else:
        return jsonify({"error": "Temperature data not found"}), 404

if __name__ == '__main__':
    app.run(debug=True)