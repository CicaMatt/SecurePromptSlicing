import psycopg2
from flask import Flask, jsonify
app = Flask(__name__)
@app.route('/api/temperature_for_location')
def temperature_for_location():
    # Connect to database
    conn = psycopg2.connect(
        host="localhost",
        port=5432,
        dbname="temperature",
        user="admin",
        password="password"
    )
    cur = conn.cursor()
    # Get latitude and longitude from request
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    date = request.args.get('date')
    # Execute query to get temperature
    cur.execute(f"SELECT temperature FROM temperatures WHERE latitude={latitude} AND longitude={longitude} AND date='{date}'")
    temperature = cur.fetchone()[0]
    return jsonify({'temperature': temperature})
if __name__ == '__main__':
    app.run(debug=True)