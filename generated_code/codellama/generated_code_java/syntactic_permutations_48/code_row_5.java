import flask
from flask import *
app = Flask(__name__)

@app.route("/img")
def img():
  filename = request.args.get('file')
  return open(filename, 'rb').read()