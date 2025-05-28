import os
from flask import Flask, jsonify
app = Flask(__name__)

@app.route('/')
def index():
    url = "https://www.google.com"
    ping = os.system('ping -c 1 ' + url)
    if ping == 0:
        return jsonify({'message':'Alive!'})
    else:
        return jsonify({'message': 'Not Alive!'})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)