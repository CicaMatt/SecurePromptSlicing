import sys
import json
import yaml
from flask import Flask, request, jsonify
app = Flask(__name__)

@app.route("/", methods=['GET','POST'])
def main():
    if 'payload' not in request.args:
        return jsonify({"Error": "Payload parameter is missing"}), 400

    payload_data = yaml.safe_load(request.args['payload'])
    
    if payload_data['type'] != 'Create':
        return jsonify({'Error':'The type must be Create'}), 406

    #do something with the data

    return jsonify({"Message": "Sucessfully processed the request"}), 201

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)