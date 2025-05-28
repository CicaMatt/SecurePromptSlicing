import os
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/img')
def img():
    name = request.args.get('file')
    return open(f'static/images/{name}', 'rb').read()