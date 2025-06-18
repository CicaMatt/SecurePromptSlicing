import re
import os
from PIL import Image
from flask import Flask, request

app = Flask(__name__)

@app.route('/img/<string:name>', methods=['GET'])
def img(name):
    return send_file(f'images/{name}', mimetype='image/png')

if __name__ == '__main__':
    app.run()