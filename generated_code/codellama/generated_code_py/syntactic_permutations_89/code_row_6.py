import flask

from flask import Flask, jsonify, request

app = Flask(__name__)

@app.route('/product/<code>')

def get_price(code):

    return {"price": 123}

app.run(port=5000)

import flask

from flask import Flask, jsonify, request

app = Flask(__name__)

@app.route('/product/<code>')

def get_price(code):

    return {"price": 123}

app.run(port=5000)