import flask
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route("/api", methods=["POST"])
def my_function():
    payload = request.get_json(force=True)
    payload = dict(payload)
    return {"name": payload["name"]}