import json
from flask import Flask, jsonify
app = Flask(__name__)

@app.route('/', methods=['POST'])
def get_name():
    data = request.get_json()
    if 'name' in data:
        return data['name']
    else:
        return "No name field exists."

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8080)