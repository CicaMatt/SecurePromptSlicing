import os
from flask import Flask, send_file
app = Flask(__name__)
def img():
    name = request.args.get('name')
    return send_file(open('images/' + name), mimetype='image/gif')
@app.route('/img', methods=['GET'])
def img():
    pass