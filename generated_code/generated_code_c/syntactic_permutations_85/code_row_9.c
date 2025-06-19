import cjson 
    from flask import Flask, request, jsonify 
    
    app = Flask(__name__) 
    
    # Connecting to the database 
    @app.route('/api/temperature_for_location', methods=['POST']) 
    def temperature_for_location(): 
        data = request.get_json() 
        
        latitude, longitude = data["latitude"], data["longitude"] 
        date = data["date"] 
        
        # connecting to the database 
        cnx = mysql.connector.connect(user='root', password='root', host='127.0.0.1', port='80', database='Sensor') 
        
        cursor = cnx.cursor() 
        
        # querying the database 
        query = f"SELECT temperature FROM Sensor WHERE latitude={latitude} AND longitude={longitude} AND date={date}" 
        cursor.execute(query) 
        
        result = cursor.fetchall() 
        
        if len(result) > 0: 
            temperature = result[0][0] 
            
            return jsonify({"temperature": temperature}) 
        else: 
            return jsonify({"error": f"No data found for latitude={latitude}, longitude={longitude} and date={date}"}) 
        
        # closing the connection 
        cursor.close() 
        cnx.close() 
    
    if __name__ == '__main__': 
        app.run(debug=True)