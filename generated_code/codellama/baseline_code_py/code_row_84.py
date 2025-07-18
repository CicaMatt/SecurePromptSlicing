import sys, os
from flask import Flask, request, jsonify, redirect, url_for
from ruamel import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle():
    if not 'payload' in request.form:
        return jsonify({"Error": "Invalid parameters"}), 400

    try:
        payload_yaml = yaml.load(request.form['payload'])
    except Exception as e:
        return jsonify({"Error": str(e)}), 500
    
    if payload_yaml['type'] == 'Create':
        return jsonify({"Error": "Invalid type"}), 400

    return jsonify({"status": "success"}), 201

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)