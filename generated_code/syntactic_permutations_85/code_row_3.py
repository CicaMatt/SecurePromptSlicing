from flask import Flask, request, jsonify
app = Flask(__name__)
@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    content = request.get_json()
    latitude = content['latitude']
    longitude = content['longitude']
    date = content['date']
    conn = sqlite3.connect('sensor.db')
    c = conn.cursor()
    c.execute("SELECT temperature FROM Sensor WHERE Latitude=? and Longitude=? and Date=?", (latitude, longitude, date))
    result = c.fetchone()
    return jsonify({'temperature': float(result[0])})
if __name__ == '__main__':
    app.run(debug=True)