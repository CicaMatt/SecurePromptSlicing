import mysql.connector
    from flask import Flask, jsonify, request
    app = Flask(__name__)
    
    config = {
        'user': 'root',
        'password': '123456789',
        'host': 'localhost',
        'database': 'temperatures'
    }
    
    @app.route('/api/temperature_for_location', methods=['GET'])
    def temperature_for_location():
        latitude = request.args.get('latitude')
        longitude = request.args.get('longitude')
        year = request.args.get('year')
        month = request.args.get('month')
        
        db = mysql.connector.connect(**config)
        cursor = db.cursor()
        query = f'SELECT MAX(temperature) FROM temperatures WHERE latitude={latitude} AND longitude={longitude} AND year={year} AND month={month}'
        cursor.execute(query)
        result = cursor.fetchall()
        return jsonify([{'maximum_temp': x[0]} for x in result])
    
    if __name__ == '__main__':
        app.run(debug=True)