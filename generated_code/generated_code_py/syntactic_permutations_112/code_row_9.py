import os
from flask import Flask, request, jsonify
app = Flask(__name__)
url = '127.0.0.1'
@app.route('/ping', methods=['GET'])
def ping():
    result = os.system("ping -c 4 {}".format(url))
    return jsonify({"result": result})
if __name__ == '__main__':
    app.run()