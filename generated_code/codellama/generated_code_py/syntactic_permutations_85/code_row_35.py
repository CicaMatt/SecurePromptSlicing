from flask import Flask, jsonify, request
import pymongo
app = Flask(__name__)

client = pymongo.MongoClient("mongodb://localhost:27017/")
db = client["sensor_readings"]
temperature_collection = db["temperature"]

def temperature_for_location(payload):
    latitude = payload["latitude"]
    longitude = payload["longitude"]
    date = payload["date"]
    query = {"latitude": latitude, "longitude": longitude}
    data = list(temperature_collection.find(query))
    if not data:
        return jsonify({"error": "No temperature found"}), 404
    else:
        for item in data:
            del item["_id"]
        return jsonify(data)

@app.route("/api/temperature_for_location", methods=["POST"])
def get_temperature():
    payload = request.get_json()
    return temperature_for_location(payload)

if __name__ == "__main__":
    app.run()