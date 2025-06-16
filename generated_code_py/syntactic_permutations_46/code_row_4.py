import flask
from flask import Flask,send_file
app = Flask(__name__)
@app.route("/img")
def img():
  name=flask.request.args.get("name")
  return send_file(f"images/{name}",as_attachment=True)