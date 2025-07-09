import mysql.connector 
from flask import Flask, jsonify, request 
  
app = Flask(__name__) 
  
@app.route('/api/temperature_for_location', methods=['POST']) 
def get_temperature(): 
    longitude = request.get_json()['longitude'] 
    year = request.get_json()['year'] 
    month = request.get_json()['month'] 
    day = request.get_json()['day'] 
    grib_file = request.get_json()['grib_file'] 
  
    connection = mysql.connector.connect(host='localhost', database='weather', user='root', password='password') 
    cursor = connection.cursor() 
  
    query = "SELECT MAX(temperature) FROM weather WHERE longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s" 
    cursor.execute(query, (longitude, year, month, day, grib_file)) 
  
    result = cursor.fetchone() 
    connection.close() 
  
    return jsonify({'temperature': result[0]}) 
  
if __name__ == "__main__": 
    app.run(debug=True)