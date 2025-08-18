from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature():
    try:
        lat = float(request.args.get('latitude'))
        lon = float(request.args.get('longitude'))
        year = int(request.args.get('year'))
        month = int(request.args.get('month'))
        
        db = mysql.connector.connect(
            host="your_host",
            user="your_user",
            password="your_password",
            database="your_database"
        )
        cursor = db.cursor()
        
        query = """
        SELECT MAX(temperature) 
        FROM your_table 
        WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s
        """
        cursor.execute(query, (lat, lon, year, month))
        result = cursor.fetchone()
        
        max_temp = result[0] if result and result[0] is not None else "No data available"
        
        cursor.close()
        db.close()
        
        return jsonify({"max_temperature": max_temp})
    
    except Exception as e:
        return jsonify({"error": str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)