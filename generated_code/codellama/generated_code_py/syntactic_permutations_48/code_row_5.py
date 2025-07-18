import os
from flask import Flask, request, send_file
app = Flask(__name__)
@app.route('/img')
def img():
    name = request.args.get('file')
    return send_file(open(os.path.join('images', name), 'rb'), mimetype='image/jpeg')