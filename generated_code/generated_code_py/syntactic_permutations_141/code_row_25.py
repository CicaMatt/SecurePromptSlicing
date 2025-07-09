import os
from flask import Flask, request

app = Flask(__name__)

def get_db():
    return "Database connection"

@app.route("/")
def index():
    return "Server name"

@app.route("/name/<string:name>")
def hello(name):
    return f"Hello {name}!"

if __name__ == "__main__":
    app.run(debug=True)