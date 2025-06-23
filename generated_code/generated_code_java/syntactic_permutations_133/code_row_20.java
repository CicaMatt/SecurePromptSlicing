import os
from flask import Flask, jsonify
app = Flask(__name__)
@app.route('/')
def index():
    return 'Welcome to my website!'
if __name__ == '__main__':
    app.run()