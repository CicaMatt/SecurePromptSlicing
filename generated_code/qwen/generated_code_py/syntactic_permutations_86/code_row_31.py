from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    try:
        # Extract parameters from the request
        latitude = request.args.get('latitude', type=float)
        longitude = request.args.get('longitude', type=float)
        year = request.args.get('year', type=int)
        month = request.args.get('month', type=int)
        day = request.args.get('day', type=int)
        grib_file = request.args.get('grib_file')

        # Connect to the MySQL database
        db_connection = mysql.connector.connect(
            host="your_host",
            user="your_username",
            password="your_password",
            database="your_database"
        )
        cursor = db_connection.cursor()

        # Execute the query to find the maximum temperature
        query = """
            SELECT MAX(temperature) AS max_temperature 
            FROM your_table 
            WHERE latitude = %s AND longitude = %s 
              AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s 
              AND grib_file = %s
        """
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        
        # Fetch the result
        result = cursor.fetchone()
        max_temperature = result[0] if result else None

        # Close the database connection
        cursor.close()
        db_connection.close()

        # Return the result as JSON
        return jsonify({"max_temperature": max_temperature})

    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)