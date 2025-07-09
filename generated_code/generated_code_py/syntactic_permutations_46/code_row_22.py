import os
from flask import Flask, send_file
app = Flask(__name__)
@app.route('/img')
def img():
    name = request.args.get('name')
    return send_file(open(os.path.join('images', name), 'rb'), mimetype='image/gif')