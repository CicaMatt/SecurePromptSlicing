from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

def get_temperature_from_db(location, date):
    try:
        connection = psycopg2.connect(
            dbname="Sensor",
            user="your_username",  # replace with your username
            password="your_password",  # replace with your password
            host="localhost"  # or your database host
        )
        cursor = connection.cursor()
        
        query = """
        SELECT temperature 
        FROM temperatures 
        WHERE location = %s AND date = %s;
        """
        cursor.execute(query, (location, date))
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
    
    location = data.get('location')
    date = data.get('date')

    if not location or not date:
        return jsonify({"error": "Missing location or date"}), 400
    
    temperature = get_temperature_from_db(location, date)
    
    if temperature is not None:
        return jsonify({"temperature": temperature}), 200
    else:
        return jsonify({"error": "Temperature data not found"}), 404

if __name__ == '__main__':
    app.run(debug=True)


