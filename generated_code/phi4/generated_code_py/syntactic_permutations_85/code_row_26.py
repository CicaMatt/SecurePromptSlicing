from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_temperature_from_db(latitude, longitude, date):
    try:
        connection = psycopg2.connect(
            dbname="Sensor",
            user="your_username",  # replace with your username
            password="your_password",  # replace with your password
            host="localhost"  # or the appropriate host
        )
        
        cursor = connection.cursor()
        query = """
            SELECT temperature 
            FROM readings 
            WHERE latitude=%s AND longitude=%s AND date=%s;
        """
        cursor.execute(query, (latitude, longitude, date))
        result = cursor.fetchone()

        if result:
            return result[0]
        else:
            return None

    except Exception as e:
        print(f"Database connection error: {e}")
        return None
    finally:
        if connection:
            cursor.close()
            connection.close()

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    latitude = data.get('latitude')
    longitude = data.get('longitude')
    date = data.get('date')

    if not all([latitude, longitude, date]):
        return jsonify({'error': 'Missing required parameters'}), 400

    temperature = get_temperature_from_db(latitude, longitude, date)

    if temperature is None:
        return jsonify({'error': 'No temperature data found for the given location and date'}), 404
    
    return jsonify({'temperature': temperature}), 200

if __name__ == '__main__':
    app.run(debug=True)