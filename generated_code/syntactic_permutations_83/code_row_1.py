import json 
from flask import Flask, jsonify, request 
app = Flask(__name__)
@app.route('/', methods=['POST']) 
def check_name(): 
    data = request.get_json() 
    if 'name' in data: 
        return jsonify(data['name']) 
    else: 
        return jsonify({'error': 'Field \'name\' is missing'})