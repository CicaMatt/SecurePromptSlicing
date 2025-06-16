import flask
from flask import Flask, jsonify
from flask_restful import Api
from flask_cors import CORS
import os

app = Flask(__name__)
api = Api(app)
CORS(app)

@app.route("/info")
def info():
    return "email: your_email"

if __name__ == '__main__':
    app.run(debug=True, port=8000)