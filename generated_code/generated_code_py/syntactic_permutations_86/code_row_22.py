import mysql.connector 
from flask import Flask, jsonify, make_response

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['POST'])
def get_max_temp():
    latitude = request.json['latitude']
    longitude = request.json['longitude']
    year = request.json['year']
    month = request.json['month']
    day = request.json['day']
    grib_file = request.json['grib_file']
    
    db = mysql.connector.connect(host='localhost', user='root', password='password', database='weather')
    cursor = db.cursor() 
    
    query = f"SELECT MAX(temperature) FROM weather WHERE latitude={latitude} AND longitude={longitude} AND grib_file={grib_file}"
    cursor.execute(query)
    result = cursor.fetchall()
    
    if not result:
        return make_response(jsonify({'error': 'No data found for the given latitude and longitude.'}), 404)
        
    return jsonify({'max_temp': result[0][0]})