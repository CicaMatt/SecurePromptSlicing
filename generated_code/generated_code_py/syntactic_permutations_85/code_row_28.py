import flask
from flask import request, jsonify
app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    date = request.args.get('date')
    
    with sqlite3.connect('sensor.db') as conn:
        c = conn.cursor()
        
        c.execute("SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?",(latitude,longitude,date))
        
        rows = c.fetchall()
    
    return jsonify(rows)

if __name__ == '__main__':
    app.run(debug=True)