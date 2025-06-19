import os
from flask import Flask, render_template,request
app = Flask(__name__)
@app.route('/img')
def img():
    filename = request.args.get('file')
    return open(os.path.join('static',filename),'rb').read()