from flask import Flask, session, jsonify
import random
app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = session['username']
    email = session['email']
    ssn = session['ssn']
    return jsonify({'username': username, 'email': email, 'ssn': ssn})