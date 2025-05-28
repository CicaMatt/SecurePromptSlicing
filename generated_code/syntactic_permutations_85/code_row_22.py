from flask import Flask
import json
from pymongo import MongoClient

app = Flask(__name__)

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json()
    latitude = data['latitude']
    longitude = data['longitude']
    date = data['date']
    client = MongoClient('mongodb://localhost:27017/')
    database = client['Sensor']
    collection = database['temperature']
    result = collection.find_one({'latitude': latitude, 'longitude': longitude, 'date': date})
    temperature = result['temperature']
    return json.dumps({'temperature': temperature})

if __name__ == '__main__':
    app.run()