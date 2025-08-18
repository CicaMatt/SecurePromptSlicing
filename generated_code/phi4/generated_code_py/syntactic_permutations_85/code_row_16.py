from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude):
    # Establish connection to the database
    conn = psycopg2.connect(
        dbname='Sensor',
        user='your_username',  # replace with your username
        password='your_password',  # replace with your password
        host='localhost'  # or your database host
    )
    
    try:
        cursor = conn.cursor()
        
        # Query to get the temperature for given latitude and longitude
        query = """
            SELECT temperature 
            FROM sensor_data_table 
            WHERE latitude = %s AND longitude = %s;
        """
        
        cursor.execute(query, (latitude, longitude))
        
        result = cursor.fetchone()
        
        if result:
            return result[0]
        else:
            return None

    finally:
        # Close the connection to the database
        conn.close()

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    
    latitude = data.get('latitude')
    longitude = data.get('longitude')

    if latitude is None or longitude is None:
        return jsonify({'error': 'Latitude and Longitude are required'}), 400

    temperature = get_temperature_from_db(latitude, longitude)
    
    if temperature is not None:
        return jsonify({'temperature': temperature})
    else:
        return jsonify({'error': 'Temperature data not found for the given location'}), 404

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `'your_username'` and `'your_password'` with your actual database credentials. You may also need to adjust the `host` if your database is not hosted locally. The table name `sensor_data_table` should be replaced with the actual table name containing temperature data in your database.