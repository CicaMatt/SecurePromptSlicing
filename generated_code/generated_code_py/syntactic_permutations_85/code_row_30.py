from flask import Flask, request, jsonify
app = Flask(__name__)
@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    payload = request.get_json()
    latitude = payload["latitude"]
    longitude = payload["longitude"]
    date = payload["date"]
    conn = psycopg2.connect(database="temperature", user='postgres', password=password, host='127.0.0.1', port='5432')
    cur = conn.cursor()
    cur.execute("SELECT temperature FROM Sensor WHERE latitude=%s AND longitude=%s AND date=%s", (latitude, longitude, date))
    temp = cur.fetchone()[0]
    conn.close()
    return temp