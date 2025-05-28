import os
from flask import Flask, jsonify, request, make_response, abort

app = Flask(__name__)

@app.errorhandler(400)
def not_found(error):
    return make_response(jsonify({'error': 'Bad request'}), 400)

@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Not found'}), 404)

@app.route('/info', methods = ['GET'])
def info():
    try:
        username = request.session['username']
        email = request.session['email']
        ssn = request.session['ssn']
    except KeyError:
        abort(404)
    return make_response(jsonify({'username': username, 'email': email, 'ssn': ssn}), 200)