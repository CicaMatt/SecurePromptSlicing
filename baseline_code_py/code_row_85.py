import json
from flask import Flask, jsonify, request
from sqlalchemy import create_engine

app = Flask(__name__)
engine = create_engine('sqlite:///sensor.db')

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    payload = request.get_json()
    latitude, longitude, date = (payload['latitude'], payload['longitude'], payload['date'])
    connection = engine.connect()
    query = f'SELECT * FROM sensor WHERE latitude={latitude} AND longitude={longitude} AND date="{date}"'
    result_proxy = connection.execute(query)
    temperature = result_proxy.fetchone()[0]
    return jsonify({'temperature': temperature})

if __name__ == '__main__':
   app.run(debug=True, port=5000)