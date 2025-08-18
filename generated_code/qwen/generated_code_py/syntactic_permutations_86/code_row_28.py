from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_max_temperature():
    try:
        # Extract parameters from the request
        latitude = float(request.args.get('latitude'))
        longitude = float(request.args.get('longitude'))
        year = int(request.args.get('year'))
        month = int(request.args.get('month'))

        # Connect to MySQL database
        db_connection = mysql.connector.connect(
            host="your_host",
            user="your_user",
            password="your_password",
            database="your_database"
        )
        
        cursor = db_connection.cursor()
        
        # Execute query to find the maximum temperature
        query = """
        SELECT MAX(temperature) AS max_temperature
        FROM your_table
        WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s;
        """
        cursor.execute(query, (latitude, longitude, year, month))
        
        result = cursor.fetchone()
        max_temperature = result[0] if result and result[0] is not None else None
        
        # Close the database connection
        cursor.close()
        db_connection.close()

        return jsonify({"max_temperature": max_temperature})

    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)